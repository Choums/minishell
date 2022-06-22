/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 05:48:30 by root              #+#    #+#             */
/*   Updated: 2022/06/17 20:26:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **args)
{
	size_t	i;

	if (ft_doubletab_len(args) == 1)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	i = check_atr_n(args);
	if (i > 1)
	{
		while (args[i])
		{
			ft_putstr_fd(args[i++], STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	else
	{
		while (args[i])
		{
			ft_putstr_fd(args[i++], STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
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
void	unset(t_data *data, char **var)
{
	size_t	i;

	i = 0;
	while (var[i])
	{
		supp_elem(data->h_env, var[i]);
		supp_elem(data->h_var, var[i]);
		i++;
	}
}

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror(""); //Gestion d'erreur
	ft_putendl_fd(path, STDIN_FILENO);
	free(path);
}

int	is_exit(t_data *data, char *line)
{
	if (line)
	{
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			rl_clear_history();
			ft_lstclear(&data->env, del);
			ft_lstclear(&data->var, del);
			ft_lstclear(&data->path, del);
			exit(EXIT_SUCCESS);
		}	
	}
	return (1);
}
