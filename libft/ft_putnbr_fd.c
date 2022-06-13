/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:54:41 by chaidel           #+#    #+#             */
/*   Updated: 2021/12/15 21:30:24 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;
	size_t		len;

	len = 0;
	if (fd < 0)
		return (len);
	nbr = n;
	if (nbr < 0)
	{
		len += ft_putchar_fd('-', fd);
		nbr *= (-1);
	}
	if (nbr > 9)
	{
		len += ft_putnbr_fd(nbr / 10, fd);
		len += ft_putnbr_fd(nbr % 10, fd);
	}
	else
		len += ft_putchar_fd(nbr + '0', fd);
	return (len);
}
