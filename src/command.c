/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:54:45 by aptive            #+#    #+#             */
/*   Updated: 2022/05/30 20:03:56 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_cup_all_cmd(char *tmp, char *tmp_cmd)
{
	int		i;

	i = 0;
	while (i < ft_strlen(tmp))
	{
		if (tmp[i] == '<' || tmp[i] == '>')
		{
			while (tmp[i] && (tmp[i] == '<' || tmp[i] == ' ' || tmp[i] == '>'))
				i++;
			while (tmp[i] && tmp[i] != ' ' )
				i++;
		}
		else if (ft_isalnum(tmp[i]))
		{
			while (tmp[i] && tmp[i] != '<' && tmp[i] != '>')
			{
				tmp_cmd = ft_straddc(tmp_cmd, tmp[i]);
				i++;
			}
		}
		else
			i++;
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
		if (ft_isalnum(cut_cmd[i]) || cut_cmd[i] == '-' || cut_cmd[i] == '.')
		{
			count_arg++;
			while (cut_cmd[i] != ' ' && cut_cmd[i])
				i++;
		}
		else if (cut_cmd[i] == 39 || cut_cmd[i] == 34)
		{
			count_arg++;
			while (cut_cmd[i] && (cut_cmd[i] != 39 || cut_cmd[i] != 34))
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
	while (i < ft_strlen(cmd))
	{
		cut = 0;
		if (ft_isalnum(cmd[i]) || cmd[i] == '-' || cmd[i] == '.')
		{
			while (cmd[i + cut] != ' ' && cmd[i + cut])
				cut++;
			table_pipe[nb_pp]->tab_cmd[++count_arg] = ft_substr(cmd, i, cut);
		}
		else if (cmd[i] == 39 || cmd[i] == 34)
		{
			while (cmd[i + cut] && (cmd[i + cut] != 39 || cmd[i + cut] != 34))
				cut++;
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
	char	**tab_command;

	cut_cmd = NULL;
	cut_cmd = ft_cup_all_cmd(table_pipe[number_pipe]->all_pipe, cut_cmd);
	count_cmd(table_pipe, number_pipe, cut_cmd);
	copy_cmd(table_pipe, number_pipe, cut_cmd);
	return (table_pipe);
}
