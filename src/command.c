/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:54:45 by aptive            #+#    #+#             */
/*   Updated: 2022/05/28 02:20:53 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_straddc_first(char c)
{
	char	*add;

	add = (char *)malloc(sizeof(char) * 2);
	if (!add)
		return (NULL);
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_straddc(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_straddc_first(c));
	add = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!add)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		add[i] = str[i];
	free(str);
	add[i++] = c;
	add[i] = '\0';
	return (add);
}

char	*ft_cup_all_cmd(char *tmp)
{
	char	*tmp_cmd;
	int		len;
	int		i;

	len = ft_strlen(tmp);
	i = 0;
	tmp_cmd = NULL;
	while (i < len)
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

t_command	**ft_count_cmd(t_command	*(*table_pipe), int	number_pipe, char *cut_cmd)
{
	int	i;
	int	count_arg;
	int	len_cut_cmd;

	i = 0;
	count_arg = 0;
	len_cut_cmd = ft_strlen(cut_cmd);
	while (i < len_cut_cmd)
	{
		if (ft_isalnum(cut_cmd[i]))
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
	table_pipe[number_pipe]->tab_cmd = malloc(sizeof(char) * (count_arg + 1));
	if (!table_pipe[number_pipe]->tab_cmd)
		return (NULL);
	return (table_pipe);
}

t_command	**ft_copy_cmd(t_command	*(*table_pipe), int	number_pipe, char *cut_cmd)
{
	int		i;
	int		count_arg;
	int		to_cut;
	int		len_cut_cmd;
	char	*tmp;

	i = 0;
	len_cut_cmd = ft_strlen(cut_cmd);
	count_arg = 0;
	while (i < len_cut_cmd)
	{
		to_cut = 0;
		if (ft_isalnum(cut_cmd[i]))
		{
			while (cut_cmd[i + to_cut] != ' ' && cut_cmd[i + to_cut])
				to_cut++;
			tmp = ft_substr(cut_cmd, i, to_cut);
			// table_pipe[number_pipe]->tab_cmd[count_arg] = ft_substr(cut_cmd, i, to_cut);
			count_arg++;
		}
		else if (cut_cmd[i] == 39 || cut_cmd[i] == 34)
		{
			while (cut_cmd[i] && (cut_cmd[i] != 39 || cut_cmd[i] != 34))
				to_cut++;
			tmp = ft_substr(cut_cmd, i, to_cut);
			// table_pipe[number_pipe]->tab_cmd[count_arg] = ft_substr(cut_cmd, i, to_cut);
			count_arg++;
		}
		else
			to_cut++;
		i += to_cut;
		printf("i : %i\n", i);
		printf("table_pipe[%i]->tab_cmd[%i]: %s\n", number_pipe, count_arg - 1, tmp);
		// free(tmp);
		// printf("table_pipe[%i]->tab_cmd[%i]: %s", number_pipe, count_arg, table_pipe[number_pipe]->tab_cmd[count_arg]);
	}
	// table_pipe[number_pipe]->tab_cmd[count_arg] = NULL;
	return (table_pipe);

}

t_command	**ft_parse_cmd(t_command	*(*table_pipe), int	number_pipe)
{
	char	*cut_cmd;
	char	**tab_command;

	cut_cmd = ft_cup_all_cmd(table_pipe[number_pipe]->all_pipe);
	table_pipe = ft_count_cmd(table_pipe, number_pipe, cut_cmd);
	ft_copy_cmd(table_pipe, number_pipe, cut_cmd);
	printf("cut_cmd : %s\n", cut_cmd);
	return (table_pipe);
}
