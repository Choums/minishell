/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:15:19 by chaidel           #+#    #+#             */
/*   Updated: 2021/11/26 12:00:50 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*tmp_src;
	char	*tmp_dst;
	size_t	dst_len;
	size_t	s;

	s = size;
	tmp_dst = dst;
	tmp_src = (char *)src;
	while (s-- && *tmp_dst)
		tmp_dst++;
	dst_len = (size_t)(tmp_dst - dst);
	s = size - dst_len;
	if (!s)
		return (dst_len + ft_strlen(tmp_src));
	while (*tmp_src)
	{
		if (s > 1)
		{
			*tmp_dst++ = *tmp_src;
			s--;
		}
		tmp_src++;
	}
	*tmp_dst = '\0';
	return (dst_len + (size_t)(tmp_src - src));
}
