/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:19:48 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/30 19:10:15 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Permet de retrouver le fichier bin de la commande donnee et verifie
 *		ses droits.
 *	Ajoute "/[filename]" a chaque path de la lst
 *	-------------------------------------
 *	
*/
char	*find_bin(t_data *data, char *bin)
{
	char	*dir;
	char	*path;
	t_list	*tmp;

	if (!get_elem(data->h_env, "PATH") && !get_elem(data->h_var, "PATH"))
		return (NULL);
	tmp = data->path;
	while (tmp)
	{
		dir = ft_strjoin(tmp->content, "/");
		path = ft_strjoin(dir, bin);
		free(dir);
		if (check_perm(path))
			return (path);
		free(path);
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_perm(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) < 0)
		return (0);
	else if ((path_stat.st_mode & __S_IFREG))
	{
		if (path_stat.st_mode & S_IXUSR)
			return (1);
		else
		{
			ft_putstr_fd("minishell: cd ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putendl_fd("Permission denied", STDERR_FILENO);
		}
	}
	else
	{
		ft_putstr_fd("minishell: cd ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd("Is a directory", STDERR_FILENO);
		// status = 1;
		return (0);
	}
	return (0);
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

	// printf("cmd: %s\n", cmd->tab_cmd[0]);
	env = lst_dup(data->h_env);
	if (pos != -1 && cmd->len_pipe > 0 && !cmd->tab_redir)
		redir_pipe(pipefd, pos, cmd->len_pipe);
	if (cmd->len_pipe > 0)
		close_unused_pipes(pipefd, pos, cmd->len_pipe);
	if (cmd->tab_redir)
	{
		// printf("in simple redir\n");
		redir(data, cmd->tab_redir);
	}
	if (is_builtin(cmd))
	{
		exec_builtin(cmd, data);
		exit(EXIT_SUCCESS);
	}
	if (execve(path, cmd->tab_cmd, env) < 0)
		exit(1);
}

void	exec_builtin(t_command *cmd, t_data *data)
{
	if (cmd->tab_redir)
	{
		redir(data, cmd->tab_redir);
	}
	run_builtin(data, cmd);
	if (cmd->tab_redir)
	{
		// fprintf(stderr, "restore\n");
		restore_redir(cmd->tab_redir);
	}
}

		// if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0
		// 	|| cmd[ft_strlen(cmd) - 1] == '/')
		// 	return (msg_err(cmd, ": No such file or directory", 127));
		// else
		// 	return (msg_err(cmd, ": Command not found", 127));
int	check_cmd(char *cmd)
{
	struct stat	path_stat;

	printf("%s\n", cmd);
	if (stat(cmd, &path_stat) == 0)
	{
		printf("%d\n", (path_stat.st_mode & __S_IFMT));
		if (((path_stat.st_mode & __S_IFMT) == __S_IFDIR)
			&& (ft_strncmp(cmd, "./", 2) == 0
				|| cmd[ft_strlen(cmd) - 1] == '/'))
			return (msg_err(cmd, ": Is a directory", 126));
		else if (((path_stat.st_mode & __S_IFMT) != __S_IFDIR)
			&& (cmd[ft_strlen(cmd) - 1] == '/'))
			return (msg_err(cmd, ": Not a directory", 126));
		else
		{
			if ((path_stat.st_mode & S_IXUSR) && (ft_strncmp(cmd, "./", 2) == 0
					|| cmd[0] == '/'))
				return (1);
			else if ((!(path_stat.st_mode & S_IXUSR))
				&& ft_strncmp(cmd, "./", 2) == 0)
				return (msg_err(cmd, ": Permission denied", 126));
		}
	}
	else if (((path_stat.st_mode & __S_IFMT) != __S_IFDIR)
		&& (cmd[ft_strlen(cmd) - 1] == '/'))
		return (msg_err(cmd, ": Not a directory", 126));
	else if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0
		|| cmd[ft_strlen(cmd) - 1] == '/')
		return (msg_err(cmd, ": No such file or directory", 127));
	return (msg_err(cmd, ": Command not found", 127));
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
	char	*cmd;

	if (get_cmd_num(cmd) == 1 && is_builtin(cmd[0]))
		exec_builtin(cmd[0], data);
	else if (get_cmd_num(cmd) == 1 && !is_builtin(cmd[0]))
	{
		cmd = get_cmd(data, cmd[0]->tab_cmd[0]);
		// printf("one child w/o builtin\n");
		child = fork();
		if (child == 0)
			process(data, cmd[0], NULL, -1, cmd);
		waitpid(child, NULL, 0);
	}
	else
	{
		// printf("multiple cmd\n");
		pipex(data, cmd);
	}
}

/*
 *	Définie la nature de la commande et retourne la valeur correspondente
 *	1	=> binaire
 *	0	=> non binaire
*/
int	define_exec()
{

}

char *get_cmd(t_data *data, char *cmd)
{
	char *path;

	path = find_bin(data, cmd);
	if (!path)
	{
		
	}
	else
		return (path);
}

void	pipex(t_data *data, t_command **cmd)
{
	int		num;
	int		i;
	pid_t	child;

	num = cmd[0]->len_pipe;
	data->pipefd = create_pipes(cmd[0]->len_pipe);
	i = 0;
	while (num >= 0)
	{
		// printf("num: %d\npos: %d\n", num, i);
		child = fork();
		if (child == 0)
		{
			// printf("cmd %d: %s\n", i, cmd[i]->tab_cmd[0]);
			if (check_cmd(cmd[i]->tab_cmd[0]))
				process(data, cmd[i], data->pipefd, i);
		}
		else if (child < 0)
			printf("error\n");
		i++;
		num--;
	}
	close_pipes(data->pipefd, cmd[0]->len_pipe);
	while (wait(NULL) > 0);
	// int ret;
	// for (int p = 0; (ret = wait(NULL) > 0); p++)
	// 	printf("---\nchild %d %s done (%d)\n---\n", p, cmd[p]->tab_cmd[0], ret);
}

int	*create_pipes(int num)
{
	int	*pipefd;
	int	i;

	i = 0;
	// printf("num %d\n", num);
	pipefd = malloc(sizeof(int) * (num * 2));
	if (!pipefd)
		printf("error\n"); // gestion d'erreur
	while (i < num)
	{
		if (pipe(&pipefd[i * 2]) < 0)
			pipe_err(pipefd, i * 2);
		i++;
	}
	// for (int p = 0; p < num + 1; p+=2)
	// 	printf("fd[%d]: %d | fd[%d]: %d\n", p, pipefd[p], p+1, pipefd[p+1]);
	return (pipefd);
}

void	close_pipes(int *pipefd, int n_pipe)
{
	int	i;

	i = 0;
	// printf("---\n");
	while (i < n_pipe * 2)
	{
		// printf("closing fd[%d]: %d\n", i, pipefd[i]);
		close(pipefd[i]);
		i++;
	}
	// printf("---\n");
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

	// fprintf(stderr, "closing unused pipes | cmd %d\n", pos);
	i = 0;
	if (pos == 0)
	{
		// fprintf(stderr, "in fst\n");
		// fprintf(stderr, "closing fd[%d]: %d\n", i , pipefd[i]);
		close(pipefd[i]);
		i+= 2;
		while (i < n_pipe * 2)
		{
			close(pipefd[i]);
			i++;
		}
	}
	else if (pos == n_pipe)
	{
		// printf("in lst\n");
		while (i < (n_pipe * 2) - 2)
		{
			close(pipefd[i]);
			i++;
		}
		// printf("closing fd[%d]: %d\n", i + 1, pipefd[i + 1]);
		close(pipefd[i + 1]);
	}
	else
	{
		// fprintf(stderr, "in mid\n");
		while (i < n_pipe * 2)
		{
			if (i != pos - 1 && i != (pos * 2) + 1)
			{
				// fprintf(stderr, "closing fd[%d]: %d\n", i, pipefd[i]);
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
	if (ft_strcmp(cmd->tab_cmd[0], "echo") == 0)
		echo(cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "cd") == 0)
		check_dir(data, cmd->tab_cmd);
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
