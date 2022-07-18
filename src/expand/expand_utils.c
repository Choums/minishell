/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:31:34 by aptive            #+#    #+#             */
/*   Updated: 2022/07/18 18:36:22 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_var(char *str)
{
	int	i;

	i = 0;
	i++;
	while (str[i] && (str[i] != ' ' && str[i] != '"' && str[i] != '$'))
		i++;
	return (i);
}

int	linear_check_tab(char **tab, int len_tab)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (++i < len_tab)
		if (!tab[i])
			count++;
	return (count);
}
