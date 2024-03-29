/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:19:48 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/28 23:29:27 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
int	process(t_data *data, t_command *cmd, int pos, t_command **t_p)
{
	char	**env;
	char	*path;

	if (pos != -1 && cmd->len_pipe > 0)
		redir_pipe(data->pipefd, pos, cmd->len_pipe);
	if (cmd->len_pipe > 0)
		close_pipes(data->pipefd, cmd->len_pipe);
	if (cmd->tab_cmd[0] && !ft_strcmp(cmd->tab_cmd[0], "exit"))
		return (0);
	if (is_builtin(cmd))
	{
		exec_builtin(cmd, data, t_p, 1);
		exit(g_signal.status);
	}
	env = lst_dup(data->h_env);
	if (cmd->tab_redir)
		if (!proc_redir(data, cmd))
			kill_kid(data, env, t_p);
	path = get_cmd(data, cmd->tab_cmd[0]);
	if (!path)
		kill_kid(data, env, t_p);
	if (execve(path, cmd->tab_cmd, env) < 0)
		exit (msg_err_ex(strerror(errno), 126));
	return (1);
}

void	exec_builtin(t_command *cmd, t_data *data, t_command **t_p, int proc)
{
	if (cmd->tab_redir)
	{
		if (!redir(data, cmd->tab_redir))
		{
			restore_redir(cmd->tab_redir);
			return ;
		}
	}
	run_builtin(data, cmd);
	if (cmd->tab_redir)
		restore_redir(cmd->tab_redir);
	if (proc)
	{
		ft_lstclear(&data->env, del);
		ft_lstclear(&data->var, del);
		ft_lstclear(&data->path, del);
		free_struc(t_p);
	}
}

/*
 *	Cree des processus enfant pour chaque commandes ainsi que les pipes
 *	Les process s'executent en meme temps
*/
void	mother_board(t_data *data, t_command **cmd)
{
	pid_t	child;
	int		status;

	g_signal.prompt = 1;
	if (get_cmd_num(cmd) == 1 && ft_strcmp(cmd[0]->tab_cmd[0], "exit") == 0)
		one_exit(data, cmd);
	else if (get_cmd_num(cmd) == 1 && is_builtin(cmd[0]))
		exec_builtin(cmd[0], data, cmd, 0);
	else if (get_cmd_num(cmd) == 1 && !is_builtin(cmd[0]))
	{
		child = fork();
		if (child == 0)
			process(data, cmd[0], -1, cmd);
		else if (child < 0)
			msg_err("fork", strerror(errno), 1);
		waitpid(child, &status, 0);
		status_child(status);
	}
	else
		pipex(data, cmd);
	unlink(".here");
	g_signal.prompt = 0;
}

void	one_exit(t_data *data, t_command **cmd)
{
	if (cmd[0]->tab_redir)
	{
		if (!redir(data, cmd[0]->tab_redir))
			return (restore_redir(cmd[0]->tab_redir));
	}
	if (cmd[0]->tab_redir)
		restore_redir(cmd[0]->tab_redir);
	exiter(data, cmd, cmd[0]->tab_cmd);
}
