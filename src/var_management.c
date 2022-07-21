/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:24:47 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/21 17:47:54 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Ajoute une var à la lst.
 *	La lst. sera init. si ce n'est pas déjà le cas
*/
void	set_var(t_data *data, char *content)
{
	if (&(*data->var) == NULL)
	{
		data->var = ft_lstnew(content);
		data->h_var = &data->var;
	}
	else
		if (get_elem(data->h_var, content) == NULL)
			ft_lstadd_back(&data->var, ft_lstnew(content));
}

/*
 *	Cherche la var dans l'env et la lst des var et renvoie sa valeur
 *	La value est a free apres son usage
*/
char	*get_var(t_data *data, char *var)
{
	t_list	*tmp;
	char	*value;

	tmp = (*data->h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var) - 1) == 0)
		{
			value = ft_substr(tmp->content, ft_strlen(var) + 1,
					ft_strlen(tmp->content) - ft_strlen(var));
			return (value);
		}
		tmp = tmp->next;
	}
	return (get_hvar(data, var));
}

/*	Cherche la var dans la lst des vars
 *	La var est renvoyé si elle existe
 *	Sinon NULL
*/
char	*get_hvar(t_data *data, char *var)
{
	t_list	*tmp;
	char	*value;

	tmp = (*data->h_var);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var) - 1) == 0)
		{
			value = ft_substr(tmp->content, ft_strlen(var) + 1,
					ft_strlen(tmp->content) - ft_strlen(var));
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 *	Cherche un element dans la list donnée et le renvoie
 *	NULL si l'elem n'existe pas
*/
char	*get_elem(t_list **head, char *var)
{
	t_list	*tmp;
	size_t	len;

	len = name_len(var);
	tmp = (*head);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, len) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 *	Renvoi la taille du nom de la var
 *	len est soit:	l'index du '='
 *					la fin du nom
*/
size_t	name_len(char *var)
{
	size_t	len;

	if (!var)
		return (0);
	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	return (len);
}
