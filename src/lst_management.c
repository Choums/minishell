/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:17:19 by root              #+#    #+#             */
/*   Updated: 2022/04/26 16:55:45 by root             ###   ########.fr       */
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
		if (ft_strnstr(tmp->content, var, ft_strlen(var)))
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
		if (ft_strnstr(tmp->content, var, ft_strlen(var)))
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