/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:14:47 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/28 19:42:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	The  shell shall give the export attribute to the variables
 *	corresponding to the specified  names,  which  shall  cause
 *	them to be in the environment of subsequently executed com‐
 *	mands. If the name of a variable is followed by =word, then
 *	the value of that variable shall be set to word.
 *	
*/

/*
 *	export [var]
 *	export -> ajoute la var a l'env.
 *	La var est mise en fin de chaine
 *	--------------------------------
 *	Seul le 1er '=' signifie la valeur, les autres ne comptent pas
 *	Une var sans value peut etre export mais elle n'apparait pas
 *	export sans arg affiche les vars sans value
 *	L'expansion des var
 *	La var '_' n'est pas affiché en export sans arg
 *	Une var déjà export ne peut plus l'être
*/
void	export(t_data *data, char *var)
{
	int		alloc;
	
	alloc = 0;
	// printf("%s\n", var);
	if (var == NULL)
	{
		display_env(data);
		return ;
	}
	if (ft_strchr(var, '$'))
	{
		var = which_dollar(data, var);
		alloc = 1;
	}
	if (ft_strchr(var, '='))
	{
		
	}
	else
		add_var(data, var);
	if (alloc)
		free(var);
}

void	add_var(t_data *data, char *var)
{
	t_list	*tmp;

	tmp = (*data->h_var);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var)) == 0
				&& get_elem(data->h_env, tmp->content) == NULL)
		{
			ft_lstadd_back(&data->env, ft_lstnew(tmp->content));
			return ;
		}
		else
			tmp = tmp->next;
	}
	if (get_elem(data->h_env, var) == NULL)
		ft_lstadd_back(&data->env, ft_lstnew(var));
}

/*	When no arguments are given, the results  are  unspecified.
 *	Affiche les var dans l'ordre ASCII
 *	La valeur des var est encadrée par des " "
 *	Affiche les var sans value
 *	-------------------------
*/
void	display_env(t_data *data)
{
	char	**env;

	env = lst_dup(data->h_env);
	sort_env(env);
	print_export(env);
	free_double_tab(env);
}

void	sort_env(char **env)
{
	char 	*swap;
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
 *	Dupplique la lst donnée et retourne un double tab
 *	1- Prendre la taille de la lst
 *	2- Init le tab
 *	3- Boucle sur la taille, chaque strdup sur chaque maillon
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
	dup = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		if (ft_strncmp(tmp->content, "_=", ft_strlen("_=")))
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