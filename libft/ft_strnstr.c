/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:34:43 by chaidel           #+#    #+#             */
/*   Updated: 2021/11/28 17:50:04 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(*to_find))
		return ((char *)(str));
	while (str[i] && i < len)
	{
		j = 0;
		while ((str[i + j] == to_find[j]) && (i + j) < len)
		{
			if (!to_find[j + 1] || j == len)
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
