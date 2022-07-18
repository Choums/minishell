/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:01:38 by root              #+#    #+#             */
/*   Updated: 2022/07/18 18:22:14 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(char **args)
{
	size_t	i;
	size_t	j;

	if (!args[1])
		return (0);
	j = ft_doubletab_len(args);
	if (j == 1)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	i = check_atr_n(args);
	if (i > 1)
		display_n(args, i, j);
	else
	{
		while (i < j)
		{
			ft_putstr_fd(args[i], STDOUT_FILENO);
			if (i++ + 1 < j)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}

int	display_n(char **args, size_t i, size_t j)
{
	while (i < j)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (i++ + 1 < j)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	return (0);
}

int	check_atr_n(char **args)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][j] && args[i][j] == '-' && args[i][j + 1] == 'n')
		{
			j++;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] && args[i][j] != 'n')
				return (1);
		}
		else
			return (i);
		i++;
	}
	return (i);
}
