/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:17:19 by root              #+#    #+#             */
/*   Updated: 2022/07/21 14:51:52 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				return (supp_fst_elem(head, tmp));
			else if (tmp->previous && tmp->next)
			{
				tmp->previous->next = tmp->next;
				tmp->next->previous = tmp->previous;
				return (ft_lstdelone(tmp, del));
			}
			else if (tmp->next == NULL)
			{
				lst = tmp;
				tmp->previous->next = NULL;
				return (ft_lstdelone(lst, del));
			}
		}
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
 *	Update la var donnée
*/
void	update_elem(t_data *data, char *var)
{
	t_list	*tmp;
	size_t	len;

	len = name_len(var);
	if (!var[len])
		len++;
	tmp = (*data->h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, len) == 0)
		{
			del(tmp->content);
			tmp->content = ft_strdup(var);
			break ;
		}
		else
			tmp = tmp->next;
	}
	if (&(*data->var) == NULL)
		return ;
	update_elem_vars(data, var, len);
}

void	update_elem_vars(t_data *data, char *var, size_t len)
{
	t_list	*tmp;

	tmp = (*data->h_var);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, len) == 0)
		{
			del(tmp->content);
			tmp->content = ft_strdup(var);
			break ;
		}
		tmp = tmp->next;
	}
}
