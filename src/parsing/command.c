/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:54:45 by aptive            #+#    #+#             */
/*   Updated: 2022/07/19 00:47:36 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_cup_all_cmd(char *tmp, char *tmp_cmd, char c, int i)
{
	while (i < (int)ft_strlen(tmp))
	{
		if (tmp[i] == '<' || tmp[i] == '>')
			i = pass_redir(tmp, i);
		else
		{
			if (tmp[i] == '\\')
				tmp_cmd = ft_straddc(tmp_cmd, tmp[i++]);
			else if (tmp[i] == '\'' || tmp[i] == '"')
			{
				c = tmp[i];
				tmp_cmd = ft_straddc(tmp_cmd, tmp[i++]);
				while (tmp[i] && tmp[i] != c)
				{
					if (tmp[i] == '\\')
						tmp_cmd = ft_straddc(tmp_cmd, tmp[i++]);
					tmp_cmd = ft_straddc(tmp_cmd, tmp[i++]);
				}
			}
			tmp_cmd = ft_straddc(tmp_cmd, tmp[i++]);
		}
	}
	return (tmp_cmd);
}

void	count_cmd(t_command	*(*table_pipe), int nb_pp, char *cut_cmd)
{
	int	i;
	int	count_arg;
	int	len_cut_cmd;

	i = 0;
	count_arg = 0;
	len_cut_cmd = ft_strlen(cut_cmd);
	while (i < len_cut_cmd)
	{
		if (cut_cmd[i] != ' ')
		{
			count_arg++;
			if (cut_cmd[i] == '\'' || cut_cmd[i] == '"')
				i += pass_quote(cut_cmd, i, 0);
			while (cut_cmd[i] != ' ' && cut_cmd[i])
				i++;
		}
		else
			i++;
	}
	table_pipe[nb_pp]->tab_cmd = ft_calloc(count_arg + 1, sizeof(char *));
}

void	copy_cmd(t_command	*(*table_pipe), int nb_pp, char *cmd)
{
	int		i;
	int		count_arg;
	int		cut;

	i = 0;
	count_arg = -1;
	while (i < (int)ft_strlen(cmd))
	{
		cut = 0;
		if (cmd[i] != ' ')
		{
			while (cmd[i + cut] && cmd[i + cut] != ' ')
			{
				if (cmd[i + cut] == '\\')
					cut++;
				else if (cmd[i + cut] == '\'' || cmd[i + cut] == '"')
					cut = pass_quote(cmd, i, cut);
				cut++;
			}
			table_pipe[nb_pp]->tab_cmd[++count_arg] = ft_substr(cmd, i, cut);
		}
		else
			cut++;
		i += cut;
	}
}

t_command	**ft_parse_cmd(t_command *(*table_pipe), int number_pipe)
{
	char	*cut_cmd;

	cut_cmd = NULL;
	cut_cmd = ft_cup_all_cmd(table_pipe[number_pipe]->all_pipe,
			cut_cmd, 'c', 0);
	count_cmd(table_pipe, number_pipe, cut_cmd);
	copy_cmd(table_pipe, number_pipe, cut_cmd);
	free(cut_cmd);
	return (table_pipe);
}
