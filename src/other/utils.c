/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:49:04 by root              #+#    #+#             */
/*   Updated: 2022/07/28 20:02:46 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

void	make_cpy(t_redirection *tab)
{
	make_cpy_in(tab);
	make_cpy_out(tab);
}

void	make_cpy_in(t_redirection *tab)
{
	tab->cpy_in = dup(0);
	close(0);
}

void	make_cpy_out(t_redirection *tab)
{
	tab->cpy_out = dup(1);
	close(1);
}
