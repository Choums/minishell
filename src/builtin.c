/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 05:48:30 by root              #+#    #+#             */
/*   Updated: 2022/07/21 15:48:29 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			g_signal.status = 1;
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
	if (!path)
	{
		ft_putstr_fd("minishell: pwd: ", STDERR);
		ft_putstr_fd("error retrieving current directory", STDERR);
		free(path);
		g_signal.status = 1;
	}
	ft_putendl_fd(path, STDOUT);
	free(path);
	return (0);
}
