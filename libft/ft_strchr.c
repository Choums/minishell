/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:26:56 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/25 17:24:06 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)(s));
		s++;
	}
	if (c == '\0')
		return ((char *)(s));
	return (NULL);
}

char	*ft_strchr_after(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)(s + 1));
		s++;
	}
	if (c == '\0')
		return ((char *)(s));
	return (NULL);
}
