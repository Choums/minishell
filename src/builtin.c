/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 05:48:30 by root              #+#    #+#             */
/*   Updated: 2022/07/05 19:27:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(char **args)
{
	size_t	i;

	if (ft_doubletab_len(args) == 1)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	i = check_atr_n(args);
	if (i > 1)
	{
		while (args[i])
		{
			if (args[i + 1])
			{
				ft_putstr_fd(args[i++], STDOUT_FILENO);
				ft_putchar_fd(' ', STDOUT_FILENO);
			}
			else
				ft_putstr_fd(args[i++], STDOUT_FILENO);
		}
	}
	else
	{
		while (args[i])
		{
			if (args[i + 1])
			{
				ft_putstr_fd(args[i++], STDOUT_FILENO);
				ft_putchar_fd(' ', STDOUT_FILENO);
			}
			else
				ft_putstr_fd(args[i++], STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
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

/*
 *	unset [var]
 *	Supp. la var
 *	Supp. le maillon de la lst. var et env.
 *	tmp->previous->next = tmp->next
 *	tmp->next->previous = tmp->previous
 *	Cas	=> Premier	| head vers next, free(tmp), head previous NULL
 *		=> Milieu	| redirection previous et next de tmp, free(tmp)
 *		=> Fin		| lst = tmp, tmp->previous->next NULL, free(lst)
*/
int	unset(t_data *data, char **var)
{
	size_t	i;

	i = 1;
	// if (!var[i])
	// {
	// 	ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
	// 	return (1);
	// }
	while (var[i])
	{
		if (get_elem(data->h_env, var[i]) || get_elem(data->h_var, var[i])
			|| is_valid_id(var[i]))
		{
			supp_elem(data->h_env, var[i]);
			supp_elem(data->h_var, var[i]);
		}
		else
		{
			ft_putstr_fd("unset: '", STDERR_FILENO);
			ft_putstr_fd(var[i], STDERR_FILENO);
			ft_putendl_fd("' not a valid identifier", STDERR_FILENO);
			//status = 1;
		}
		i++;
	}
	return (0);
}

int	is_valid_id(char *var)
{
	size_t	i;
	int		first_alpha;

	first_alpha = 0;
	i = 0;
	if (!var || !var[i])
		return (0);
	while (var[i])
	{
		if (ft_isalpha(var[i]) || var[i] == '_')
			first_alpha = 1;
		else if (!first_alpha | !ft_isalnum(var[i]) | !(var[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putendl_fd(path, STDIN_FILENO);
	free(path);
}
