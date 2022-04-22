/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:57:10 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/22 11:07:41 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*another;

	another = malloc(sizeof(*another));
	if (!another)
		return (NULL);
	another->content = content;
	another->next = NULL;
	another->previous = NULL;
	return (another);
}
