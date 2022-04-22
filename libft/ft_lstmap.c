/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:10:06 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/22 11:13:20 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, char *(*f)(char *), void (*del)(char *))
{
	t_list	*elem;
	t_list	*new_lst;

	if (!lst || !f || !del)
		return (NULL);
	elem = ft_lstnew((*f)(lst->content));
	if (!elem)
	{
		ft_lstclear(&new_lst, del);
		return (NULL);
	}
	new_lst = elem;
	lst = lst->next;
	while (lst)
	{
		elem = ft_lstnew((*f)(lst->content));
		if (!elem)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, elem);
		lst = lst->next;
	}
	return (new_lst);
}
