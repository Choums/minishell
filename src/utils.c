/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:49:04 by root              #+#    #+#             */
/*   Updated: 2022/05/31 21:04:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	print_double_tab(char **tab)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (tab[len])
		len++;
	while (i < len)
		ft_putendl_fd(tab[i++], STDERR_FILENO);
}

void	ft_err(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}
