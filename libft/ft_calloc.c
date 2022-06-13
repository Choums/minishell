/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:34:49 by chaidel           #+#    #+#             */
/*   Updated: 2021/12/10 17:19:39 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t length, size_t type)
{
	void	*ptr;

	ptr = malloc(type * length);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, length * type);
	return (ptr);
}
