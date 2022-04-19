/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:26:27 by chaidel           #+#    #+#             */
/*   Updated: 2021/11/29 15:27:30 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size <= 0)
		return (src_len);
	if (src_len >= size)
		src_len = size - 1;
	ft_memcpy(dst, src, src_len);
	dst[src_len] = '\0';
	return (ft_strlen(src));
}
