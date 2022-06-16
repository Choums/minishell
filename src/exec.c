/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:19:48 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/16 20:35:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Permet de retrouver le fichier bin de la commande donnee et verifie
 *		ses droits.
 *	Ajoute "/[filename]" a chaque path de la lst
*/
char	*find_bin(t_list *lst_path, char *bin)
{
	char	*dir;
	char	*path;

	while (lst_path)
	{
		dir = ft_strjoin(lst_path->content, "/");
		path = ft_strjoin(dir, bin);
		free(dir);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		lst_path = lst_path->next;
	}
	return (NULL);
}

/*
 *	Child processus
 *	Trouve le path de la commande et l'execute
 *	-------------------------------------
 *	redir pipe et redir file
 *	ls > outfile | wc
 *	ls ecrit dans outfile, wc ne recoit rien
 *	ls | < infile wc
 *	wc ne lit que le infile
*/
void	process(t_data *data, t_command *cmd, int *pipefd, int pos)
{
	char	*path;
	char	**env;

	printf("cmd: %s | len: %d\n", cmd->tab_cmd[0], cmd->len_pipe);
	env = lst_dup(data->h_env);
	if (cmd->tab_redir)
	{
		printf("in simple redir\n");
		redir(data, cmd->tab_redir);
	}
	if (pos != -1 && cmd->len_pipe > 0)
		redir_pipe(pipefd, pos, cmd->len_pipe);
	if (is_builtin(cmd))
	{
		printf("in builtin\n");
		run_builtin(data, cmd);
		exit(EXIT_SUCCESS);
	}
	if (1)
	{
		printf("cmd: %s\n", cmd->tab_cmd[0]);
		close_unused_pipes(pipefd, pos, cmd->len_pipe);
	}
	path = find_bin(data->path, cmd->tab_cmd[0]);
	if (execve(path, cmd->tab_cmd, env) < 0)
		return ; // error
}

/*
 *	Cree des processus enfant pour chaque commandes ainsi que les pipes
 *	Les process s'executent en meme temps
 *	-------------------------------------
 *	Ordre des process
 *	2 a la fois
 *	echo salut > outfile | wc -l >> outfile | cat | ls
 *	echo et wc on ecrit dans le outfile
 *	PAR CONTRE ls devance le cat et affiche les fichers 
 *		dont outfile avec les ecritures
 *	-------------------------------------
 *	double redir
 *	echo salut > infile > outfile
 *	les 2 fichiers sont crees
 *	salut n'est ecrit que dans outfile
 *	ouverture et redir de gauche a droite
 *	-------------------------------------
 *	builtin
 *	cd ~ | ls (dans un dossier autre que le HOME)
 *	le 1er process se rend au HOME mais ls affiche le dossier actuel
 *	echo salut
 *	la commande est executé via sa fontion dans le process parent
 *	echo salut | wc
 *	les 2 cmd sont fork, en cas de pipe les builtins ont leur propre process
*/
void	mother_board(t_data *data, t_command **cmd)
{
	pid_t	child;

	if (get_cmd_num(cmd) == 1 && is_builtin(cmd[0]))
		run_builtin(data, cmd[0]);
	else if (get_cmd_num(cmd) == 1 && !is_builtin(cmd[0]))
	{
		// printf("one child w/o builtin\n");
		child = fork();
		if (child == 0)
			process(data, cmd[0], NULL, -1);
		waitpid(0, NULL, 0);
	}
	else
	{
		// printf("multiple cmd\n");
		pipex(data, cmd);
	}
}

void	pipex(t_data *data, t_command **cmd)
{
	int		*pipefd;
	int		num;
	int		i;
	pid_t	child;

	num = cmd[0]->len_pipe;
	pipefd = create_pipes(cmd[0]->len_pipe);
	i = 0;
	while (num >= 0)
	{
		// printf("num: %d\npos: %d\n", num, i);
		child = fork();
		if (child == 0)
		{
			// printf("cmd %d: %s\n", i, cmd[i]->tab_cmd[0]);
			process(data, cmd[i], pipefd, i);
		}
		else if (child < 0)
			printf("error\n");
		i++;
		num--;
	}
	close_pipes(pipefd, cmd[0]->len_pipe);
	while (wait(NULL) > 0);
		// printf("child stoped\n");
}

int	*create_pipes(int num)
{
	int	*pipefd;
	int	i;

	i = 0;
	printf("num %d\n", num);
	pipefd = malloc(sizeof(int) * (num * 2));
	if (!pipefd)
		pipe_err(pipefd, i);
	while (i < num)
	{
		if (pipe(&pipefd[i * 2]) < 0)
			pipe_err(pipefd, i);
		printf("fd %d: %d | fd %d: %d\n", i, pipefd[i], i+1, pipefd[i+1]);
		i++;
	}
	return (pipefd);
}

void	close_pipes(int *pipefd, int n_pipe)
{
	int	i;

	i = 0;
	while (i < n_pipe)
	{
		// printf("ni: %d | i: %d\n", n_pipe - 1, i);
		close(pipefd[i]);
		i++;
	}
	free(pipefd);
}

/*
 *	Ferme les pipes non utilisé par le child actuel
 *	num	=> nbr total de pipes
 *	i	=> ordre de la cmd
 *	n et j sont les compteurs respectifs
 *	-------------------------------------
 *	cmd[0]
 *	écrit dans l'entrée du 1er pipe
 *	-------------------------------------
 *	cmd[1]
 *	Lis dans la sortie du 1er pipe
 *	écrit dans l'entrée du pipe suivant
 *	-------------------------------------
 *	cmd[2]
 *	Lis dans la sortie du pipe précédent
 *	-------------------------------------
*/
void	close_unused_pipes(int *pipefd, int pos, int n_pipe)
{
	int	i;

	printf("closing unused pipes | cmd %d\n", pos);
	i = 0;
	if (pos == 0)
	{
		close(pipefd[i]);
		i+= 2;
		while (i < n_pipe)
		{
			close(pipefd[i]);
			i++;
		}
	}
	else if (pos == n_pipe)
	{
		printf("in lst\n");
		while (i < n_pipe - 1)
		{
			close(pipefd[i]);
			i++;
		}
		printf("closing fd[%d]: %d\n", i + 1, pipefd[i + 1]);
		close(pipefd[i + 1]);
	}
	else
	{
		while (i < n_pipe)
		{
			if (i != pos - 1)
			{
				close(pipefd[i]);
			}
			if (i != pos)
			{
				close(pipefd[i]);
			}
			i++;
		}
	}
}

int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->tab_cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "exit") == 0)
		return (1);
	else
		return (0);
}

void	run_builtin(t_data *data, t_command *cmd)
{
	printf("builin run\n");
	if (ft_strcmp(cmd->tab_cmd[0], "echo") == 0)
		echo(cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "cd") == 0)
		change_dir(data->h_env, cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->tab_cmd[0], "export") == 0)
		export(data, cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "unset") == 0)
		unset(data, cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "env") == 0)
		print_env(data->h_env);
	else if (ft_strcmp(cmd->tab_cmd[0], "exit") == 0)
		is_exit(data, cmd->tab_cmd[0]);
}
