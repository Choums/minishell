/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:46:05 by tdelauna          #+#    #+#             */
/*   Updated: 2022/06/29 18:55:00 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "env") || !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	struc_len(t_command **table_pipe)
{
	int	i;

	i = 0;
	while (table_pipe[i])
		i++;
	return (i);
}

void	tokenizer_cmd(t_command **t_p, int nb_pp, t_data	*data)
{
	int		i;
	char	*path;

	i = ft_doubletab_len(t_p[nb_pp]->tab_cmd);
	t_p[nb_pp]->tab_token = ft_calloc(i + 1, sizeof(char *));
	if (!t_p[nb_pp]->tab_token)
		return ;
	i = -1;
	while (++i < ft_doubletab_len(t_p[nb_pp]->tab_cmd))
	{
		t_p[nb_pp]->tab_token[i] = ft_calloc(2, sizeof(char));
		path = find_bin(data, t_p[nb_pp]->tab_cmd[i]);
		if (path)
		{
			t_p[nb_pp]->tab_token[i][0] = '2';
			free(path);
		}
		else if (check_builtin(t_p[nb_pp]->tab_cmd[i]) && struc_len(t_p) > 1)
			t_p[nb_pp]->tab_token[i][0] = '4';
		else if (check_builtin(t_p[nb_pp]->tab_cmd[i]) && struc_len(t_p) == 1)
			t_p[nb_pp]->tab_token[i][0] = '1';
		else
			t_p[nb_pp]->tab_token[i][0] = '3';
	}
}

void	tokenizer_redir_in(t_command **t_p, int np)
{
	int	i;
	int	j;

	if (t_p[np]->tab_redir)
	{
		i = ft_doubletab_len(t_p[np]->tab_redir->in);
		t_p[np]->tab_redir->token_in = ft_calloc(i + 1, sizeof(char *));
		if (!t_p[np]->tab_redir->token_in)
			return ;
		i = 0;
		j = 0;
		while (i < ft_doubletab_len(t_p[np]->tab_redir->in))
		{
			if (t_p[np]->all_pipe[j] == '<')
				t_p[np]->tab_redir->token_in[i] = ft_calloc(2, sizeof(char));
			if (t_p[np]->all_pipe[j] == '<' && t_p[np]->all_pipe[j + 1] == '<')
			{
				t_p[np]->tab_redir->token_in[i++][0] = '2';
				j++;
			}
			else if (t_p[np]->all_pipe[j] == '<')
				t_p[np]->tab_redir->token_in[i++][0] = '1';
			j++;
		}
	}
}

void	tokenizer_redir_out(t_command **t_p, int np)
{
	int	i;
	int	j;

	if (t_p[np]->tab_redir)
	{
		i = ft_doubletab_len(t_p[np]->tab_redir->out);
		t_p[np]->tab_redir->token_out = ft_calloc(i + 1, sizeof(char *));
		if (!t_p[np]->tab_redir->token_out)
			return ;
		i = 0;
		j = 0;
		while (i < ft_doubletab_len(t_p[np]->tab_redir->out))
		{
			if (t_p[np]->all_pipe[j] == '>')
				t_p[np]->tab_redir->token_out[i] = ft_calloc(2, sizeof(char));
			if (t_p[np]->all_pipe[j] == '>' && t_p[np]->all_pipe[j + 1] == '>')
			{
				t_p[np]->tab_redir->token_out[i++][0] = '2';
				j++;
			}
			else if (t_p[np]->all_pipe[j] == '>')
				t_p[np]->tab_redir->token_out[i++][0] = '1';
			j++;
		}
	}
}
