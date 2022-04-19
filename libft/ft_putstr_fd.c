/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:40:06 by chaidel           #+#    #+#             */
/*   Updated: 2021/12/15 20:25:15 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (s && fd >= 0)
	{
		len = ft_strlen(s);
		write(fd, s, len);
		return (len);
	}
	return (len);
}
