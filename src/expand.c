/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:38:11 by tdelauna          #+#    #+#             */
/*   Updated: 2022/07/05 04:38:57 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char *str_to_expand(t_data *data, char *str)
// {
// 	char *expand;
// 	int	k;

// 	k = 0;

// 	int place_dollar = get_dollar_pos(str);
// 	if (str[place_dollar + 1] == '?')
// 	{
// 		expand = ft_itoa(g_signal.status);
// 		while (str[place_dollar + 1 + ++k])
// 			expand = ft_straddc(expand, str[place_dollar + 1 + ++k]);
// 	}
// 	else
// 		expand = which_dollar(data, str);
// 	free(str);
// 	return (expand);
// }

// void	go_expand(t_data *data, t_command *(*table_pipe))
// {
// 	char	*expand;
// 	int		i;
// 	int		j;
// 	char	**tab;
// 	int		z;

// 	i = 0;
// 	j = 0;
// 	expand = NULL;
// 	while (table_pipe[i])
// 	{
// 		while (table_pipe[i]->tab_cmd[j])
// 		{
// 			if (ft_strchr(table_pipe[i]->tab_cmd[j], '$')
// 				&& !ft_strchr(table_pipe[i]->tab_token[j], '4'))
// 			{
// 				tab = ft_split(table_pipe[i]->tab_cmd[j], ' ');
// 				// for(int y = 0; tab[y]; y++)
// 				// 	printf("tab_before %i: %s\n", y, tab[y]);
// 				z = 0;
// 				while (tab[z])
// 				{
// 					if (ft_strchr(table_pipe[i]->tab_cmd[j], '$'))
// 						tab[z] = str_to_expand(data, tab[z]);
// 					z++;
// 				}
// 				// for(int y = 0; tab[y]; y++)
// 				// 	printf("tab %i: %s\n", y, tab[y]);
// 				z = -1;
// 				while (tab[++z])
// 				{
// 					expand =  ft_join(expand, tab[z]);
// 					if (tab[z + 1])
// 						expand = ft_straddc(expand, ' ');
// 				}
// 				free_double_tab(tab);
// 				free(table_pipe[i]->tab_cmd[j]);
// 				table_pipe[i]->tab_cmd[j] = expand;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	go_expand(t_data *data, t_command *(*table_pipe))
{
	char	*expand;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (table_pipe[i])
	{
		while (table_pipe[i]->tab_cmd[j])
		{
			k = 0;
			if (ft_strchr(table_pipe[i]->tab_cmd[j], '$')
				&& !ft_strchr(table_pipe[i]->tab_token[j], '4'))
			{
				int place_dollar = get_dollar_pos(table_pipe[i]->tab_cmd[j]);
				if (table_pipe[i]->tab_cmd[j][place_dollar + 1] != ' ')
				{
					if (table_pipe[i]->tab_cmd[j][place_dollar + 1] == '?')
					{
						expand = ft_itoa(g_signal.status);
						while (table_pipe[i]->tab_cmd[j][place_dollar + 1 + ++k])
							expand = ft_straddc(expand, table_pipe[i]->tab_cmd[j][place_dollar + 1 + k]);
					}
					else
						expand = which_dollar(data, table_pipe[i]->tab_cmd[j]);
					free(table_pipe[i]->tab_cmd[j]);
					table_pipe[i]->tab_cmd[j] = expand;
				}
				// printf("expand : %s\n", expand);
			}
			j++;
		}
		i++;
	}
}


// void	go_expand(t_data *data, t_command *(*table_pipe))
// {
// 	char	*expand;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	j = 0;
// 	expand = NULL;
// 	while (table_pipe[i])
// 	{
// 		while (table_pipe[i]->tab_cmd[j])
// 		{
// 			k = 0;
// 			while (table_pipe[i]->tab_cmd[j][k])
// 			{
// 				if (ft_strchr(table_pipe[i]->tab_cmd[j], '$')
// 				&& !ft_strchr(table_pipe[i]->tab_token[j], '4'))
// 				{
// 					if (table_pipe[i]->tab_cmd[j][k] == '$' && table_pipe[i]->tab_cmd[j][k + 1] == ' ')
// 							expand  = ft_straddc(expand, table_pipe[i]->tab_cmd[j][k++]);
// 					else if (table_pipe[i]->tab_cmd[j][k] == '$' && table_pipe[i]->tab_cmd[j][k + 1] == '?')
// 					{
// 						expand = ft_itoa(g_signal.status);
// 						k += 2;
// 					}
// 					else if (table_pipe[i]->tab_cmd[j][k] == '$')
// 						expand = which_dollar(data, table_pipe[i]->tab_cmd[j]);
// 					else
// 					{
// 						expand = ft_straddc(expand, table_pipe[i]->tab_cmd[j][++k]);
// 					}
// 				}
// 				k++;
// 			}
// 			if (expand)
// 			{
// 				free(table_pipe[i]->tab_cmd[j]);
// 				table_pipe[i]->tab_cmd[j] = expand;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
