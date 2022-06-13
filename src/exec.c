/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:19:48 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/13 18:38:28 by chaidel          ###   ########.fr       */
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
 *
*/
void	process(t_data *data, t_command *cmd, int pipefd[][2], int pos)
{
	char	*path;
	char	**env;

	env = lst_dup(data->h_env);
	if (cmd->tab_redir)
		redir(data, cmd->tab_redir);
	if (pos != -1 && ni > 1)
		redir_pipe(pipefd, pos);
	if (is_builtin(cmd))
	{
		run_builtin(data, cmd);
		exit(EXIT_SUCCESS);
	}
	if (ni > 1)
		close_unused_pipes(pipefd, pos);
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

	ni = 0;
	if (is_builtin(cmd[0]) && get_cmd_num(cmd) == 1)
		run_builtin(data, cmd[0]);
	else if (!is_builtin(cmd[0]) && get_cmd_num(cmd) == 1)
	{
		printf("one child w/o builtin\n");
		child = fork();
		if (child == 0)
			process(data, cmd[0], NULL, -1);
		waitpid(0, NULL, 0);
	}
	else
	{
		printf("multiple cmd\n");
		pipex(data, cmd);
	}
}

void	pipex(t_data *data, t_command **cmd)
{
	int		pipefd[get_cmd_num(cmd) - 1][2];
	int		num;
	int		i;
	pid_t	child;

	i = 0;
	num = get_cmd_num(cmd);
	ni = num;
	while (i < num)
	{
		if (pipe(pipefd[i]) < 0)
			return ; //gerer l'error
		i++;
	}
	i = 0;
	while (num > 0)
	{
		printf("num: %d\npos: %d\n", num, i);
		child = fork();
		if (child == 0)
		{
			printf("cmd: %d\n", i);
			process(data, cmd[i], pipefd, i);
		}
		else if (child < 0)
			printf("error\n");
		i++;
		num--;
	}
	close_pipes(pipefd);
	while (wait(NULL) > 0)
		printf("child stoped\n");
}

void	close_pipes(int pipefd[][2])
{
	int	i;

	i = 0;
	while (i < ni - 1)
	{
		printf("ni: %d | i: %d\n", ni - 1, i);
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

void	close_unused_pipes(int pipefd[][2], int pos)
{
	int	i;

	i = 0;
	if (pos == 0)
	{
		close(pipefd[0][0]);
		i++;
		while (i < ni - 1)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
	}
	else if (pos == ni - 1)
	{
		while (i < ni - 2)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
		close(pipefd[i][1]);
	}
	else
	{
		while (i < ni - 1)
		{
			if (i != pos - 1)
				close(pipefd[i][0]);
			if (i != pos)
				close(pipefd[i][1]);
			i++;
		}
	}
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
// void	close_unused_pipe(int **pipefd, int i)
// {
// 	size_t	n;
// 	size_t	num;
// 	size_t	j;

// 	num = 0;
// 	while (pipefd[num])
// 		num++;
// 	j = 0;
// 	n = 0;
// 	if (i == 0)
// 	{
// 		while (n < num)
// 		{
// 			j = 0;
// 			while (j <= 1)
// 			{
				
// 			}
// 			n++;
// 		}
// 		close(pipefd[0][0]);
// 		close(pipefd[1][1]);
// 		close(pipefd[1][0]);
// 	}
// }

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
