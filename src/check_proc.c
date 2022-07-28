/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:18:27 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/28 18:22:36 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	kill_kid(t_data *data, char **env, t_command **tab)
{
	ft_lstclear(&data->env, del);
	ft_lstclear(&data->var, del);
	ft_lstclear(&data->path, del);
	free_double_tab(env);
	free_struc(tab);
	exit(g_signal.status);
}

void	status_child(int status)
{
	if ((WIFEXITED (status)))
		g_signal.status = WEXITSTATUS (status);
	if (WIFSIGNALED(status))
		g_signal.status = WTERMSIG(status) + 128 - 14;
}

int	proc_redir(t_data *data, t_command *cmd)
{
	if (!redir(data, cmd->tab_redir))
	{
		restore_redir(cmd->tab_redir);
		return (0);
	}
	close_cpy(cmd->tab_redir);
	return (1);
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
