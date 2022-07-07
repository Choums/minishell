/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:19:48 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/07 09:00:47 by aptive           ###   ########.fr       */
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
			msg_err(path, "permission denied", 126);
	}
	else
		msg_err(path, "is a directory", 126);
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
int	process(t_data *data, t_command *cmd, int pos)
{
	char	**env;
	char 	*path;

	// printf("trucxxxxxxxxxx\n");
	// printf("cmd: %s\n", cmd->tab_cmd[0]);
	if (pos != -1 && cmd->len_pipe > 0 && !cmd->tab_redir)
		redir_pipe(data->pipefd, pos, cmd->len_pipe);
	if (cmd->len_pipe > 0)
		close_unused_pipes(data->pipefd, pos, cmd->len_pipe);
	if (cmd->tab_redir)
		redir(data, cmd->tab_redir);
	if (!ft_strcmp(cmd->tab_cmd[0], "exit"))
		return ;
	if (is_builtin(cmd))
	{
		exec_builtin(cmd, data);
		exit(EXIT_SUCCESS);
	}
	env = lst_dup(data->h_env);
	path = get_cmd(data, cmd->tab_cmd[0]);
	// printf("g_signal.status process: %i\n",g_signal.status);

	if (!path)
	{
		ft_lstclear(&data->env, del);
		ft_lstclear(&data->var, del);
		ft_lstclear(&data->path, del);
		free_double_tab(env);
		// printf("g_signal.status process2: %i\n",g_signal.status);
		// return(g_signal.status);
		exit(g_signal.status);
	}
	if (execve(path, cmd->tab_cmd, env) < 0)
		exit(EXIT_FAILURE);

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

	if (stat(cmd, &path_stat) == 0)
	{
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
	return (msg_err(cmd, ": command not found", 127));
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

	if (get_cmd_num(cmd) == 1 && ft_strcmp(cmd[0]->tab_cmd[0], "exit") == 0)
	{
		exiter(data, cmd, cmd[0]->tab_cmd);
	}
	else if (get_cmd_num(cmd) == 1 && is_builtin(cmd[0]))
	{
		exec_builtin(cmd[0], data);
	}
	else if (get_cmd_num(cmd) == 1 && !is_builtin(cmd[0]))
	{
		// printf("g_signal.status mother 2 : %i\n", g_signal.status);
		// printf("one child w/o builtin\n");
		int	test = 0;
		child = fork();
		if (child == 0)
		{
			test = process(data, cmd[0], -1);
		}

		int status;
		if ((0 < waitpid (child, &status, 0)) && (WIFEXITED (status)))
			g_signal.status = WEXITSTATUS (status);

		// waitpid(child, NULL, 0);
		// printf("test : %i\n", test);

		// status_child(child);

		// printf("wexitstatus : %i\n",WEXITSTATUS(child));
		// if (g_signal.nt_status == 0)
		// 	status_child(child);
	}
	else
	{
		pipex(data, cmd);
	}
	get_cmd_num(cmd);

}

void		status_child(int pid)
{
	// printf("ICII\n");
	// g_signal.status = 0;
	if (WIFEXITED(pid))
	{
		printf("WIFEXITED\n");
		// g_signal.status = WEXITSTATUS(pid);
		// printf("WIFEXITED : %i\n", WEXITSTATUS(pid));
	}
	if (WIFSIGNALED(pid))
	{
		printf("WIFSIGNALED\n");
		g_signal.status = WTERMSIG(pid);
		if (g_signal.status != 131)
			g_signal.status += 128;
		// printf("WIFSIGNALED : %i\n", WTERMSIG(pid));
	}
	// printf("g_signal.status child: %i\n", g_signal.status);

}

char *get_cmd(t_data *data, char *cmd)
{
	char *path;

	path = find_bin(data, cmd);
	if (!path)
	{
		if (check_cmd(cmd))
		{
			// printf("HERRRRRRRRRRRRRRRRRRR\n");
			return (cmd);
		}
		else
		{
			// printf("g_signal.status get_cmd  : %i\n", g_signal.status);
			return (NULL);
		}
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
			process(data, cmd[i], i);
			exiter(data, cmd, cmd[i]->tab_cmd);
		}
		else if (child < 0)
			printf("error\n");
		i++;
		num--;
	}
	close_pipes(data->pipefd, cmd[0]->len_pipe);
	while (wait(NULL) > 0);
	// status_child(child);
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
	// printf("g_signal.status is_builtin  : %i\n", g_signal.status);
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
	else
		return (0);
}

void	run_builtin(t_data *data, t_command *cmd)
{
	if (ft_strcmp(cmd->tab_cmd[0], "echo") == 0)
		g_signal.status = echo(cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "cd") == 0)
		g_signal.status = check_dir(data, cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "pwd") == 0)
		g_signal.status = pwd();
	else if (ft_strcmp(cmd->tab_cmd[0], "export") == 0)
		g_signal.status = export(data, cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "unset") == 0)
		g_signal.status = unset(data, cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "env") == 0)
		g_signal.status = print_env(data->h_env);
}
