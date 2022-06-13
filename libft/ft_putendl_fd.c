/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putendl_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:46:35 by chaidel           #+#    #+#             */
/*   Updated: 2021/12/11 10:12:49 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (s && fd >= 0)
	{
		len = ft_putstr_fd(s, fd);
		write(fd, "\n", 1);
		return (len + 1);
	}
	return (len);
}
