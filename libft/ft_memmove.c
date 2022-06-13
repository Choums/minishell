/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:06:28 by chaidel           #+#    #+#             */
/*   Updated: 2021/11/25 19:34:59 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*tmp_dst;
	const char	*tmp_src;

	tmp_src = (const char *)src;
	tmp_dst = (char *)dest;
	if (!tmp_dst && !tmp_src)
		return (NULL);
	if (tmp_dst > tmp_src)
		while (len--)
			tmp_dst[len] = tmp_src[len];
	else
		ft_memcpy(tmp_dst, tmp_src, len);
	return (dest);
}
