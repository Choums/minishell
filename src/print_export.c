/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:22:28 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/21 14:54:51 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	When no arguments are given, the results  are  unspecified.
 *	Affiche les var dans l'ordre ASCII
 *	La valeur des var est encadrée par des " "
 *	Affiche les var sans value
 *	-------------------------
*/
int	display_env(t_data *data)
{
	char	**env;

	env = lst_dup(data->h_env);
	sort_env(env);
	print_export(env);
	free_double_tab(env);
	return (0);
}

void	sort_env(char **env)
{
	char	*swap;
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				swap = env[i];
				env[i] = env[j];
				env[j] = swap;
			}
			j++;
		}
		i++;
	}
}

void	print_export(char **env)
{
	size_t	i;
	size_t	j;
	size_t	egal;

	i = 0;
	while (env[i])
	{
		j = 0;
		egal = 1;
		ft_putstr_fd("declare -x ", STDIN_FILENO);
		while (env[i][j])
		{
			ft_putchar_fd(env[i][j], STDIN_FILENO);
			if (env[i][j] == '=' && egal--)
				ft_putchar_fd('"', STDIN_FILENO);
			j++;
		}
		if (!egal)
			ft_putchar_fd('"', STDIN_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		i++;
	}
}

/*
 *	Dupplique la lst donnée et retourne un double tab.
 *	1- Prendre la taille de la lst.
 *	2- Init le tab.
 *	3- Boucle sur la taille, dupplique chaque maillon.
*/
char	**lst_dup(t_list **head)
{
	size_t	len;
	size_t	i;
	char	**dup;
	t_list	*tmp;

	i = 0;
	tmp = (*head);
	len = get_lst_len(head) - 1;
	if (get_elem(head, "_="))
		len++;
	dup = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	dup[len] = NULL;
	return (dup);
}

size_t	get_lst_len(t_list **head)
{
	t_list	*tmp;
	size_t	len;

	tmp = (*head);
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
