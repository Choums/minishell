/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:17:19 by root              #+#    #+#             */
/*   Updated: 2022/05/19 20:10:19 by chaidel          ###   ########.fr       */
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
		ft_lstadd_back(&data->var, ft_lstnew(content));
}

/*
 *	Retire le maillon de la chaine
*/
void	supp_elem(t_list **head, char *var)
{
	t_list	*tmp;
	t_list	*lst;
	
	tmp = (*head);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var)) == 0)
		{
			if (tmp->previous == NULL)
			{
				supp_fst_elem(head, tmp);
				return ;
			}
			else if (tmp->previous && tmp->next)
			{
				tmp->previous->next = tmp->next;
				tmp->next->previous = tmp->previous;	
				ft_lstdelone(tmp, del);
				return ;
			}
			else if (tmp->next == NULL)
			{
				lst = tmp;
				tmp->previous->next = NULL;
				ft_lstdelone(lst, del);
				return ;
			}
		}
		else
			tmp = tmp->next;
	}
}

void	supp_fst_elem(t_list **head, t_list *tmp)
{
	if (*head == NULL)
		return ;
	if ((*head)->next == NULL)
	{
		ft_lstdelone(tmp, del);
		(*head) = NULL;
	}
	else
	{
		(*head) = tmp->next;
		ft_lstdelone(tmp, del);
		(*head)->previous = NULL;
	}
}

/*
 *	La var doit se terminer par le "="
*/
void	update_elem(t_list **head, char *var, char *content)
{
	t_list	*tmp;
	char	*new;

	tmp = (*head);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var)) == 0)
		{
			del(tmp->content);
			new = ft_strjoin(var, content);
			tmp->content = ft_strdup(new);
			free(new);
			return ;
		}
		else
			tmp	= tmp->next;
	}
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
		if (ft_strncmp(tmp->content, var, ft_strlen(var)) == 0)
		{
			value = ft_substr(tmp->content, ft_strlen(var) + 1, ft_strlen(tmp->content) - ft_strlen(var));
			return (value);
		}
		else
			tmp = tmp->next;
	}
	tmp = (*data->h_var);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var)) == 0)
		{
			value = ft_substr(tmp->content, ft_strlen(var) + 1, ft_strlen(tmp->content) - ft_strlen(var));
			return (value);
		}
		else
			tmp = tmp->next;
	}
	return (NULL);
}

/*
 *	Définie si la commande commence par un '$'
 *	Vérifie ensuite si la valeur recheché est '?' ou le nom d'une var
 *	Si aucun des deux, une valeur NULL est renvoyé
 *	VAR=value
 *	$VAR
*/
char	*which_dollar(t_data *data, char *command)
{
	char	*var;
	char	*value;

	if (command[0] == '$' && command[1])
	{
		if (command[1] == '?')
			return (0); //Signaux a faire
		var = ft_substr(command, 1, ft_strlen(command) + 1);
		value = get_var(data, var);
		free(var);
		return (value);
	}
	return (NULL);
}


/*
 *	DEBUG
 *	PRINT LA LST DONNEES 
*/
void	print_vars(t_list **head)
{
	t_list	*tmp;

	tmp = (*head);
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}