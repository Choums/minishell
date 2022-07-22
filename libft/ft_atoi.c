/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:30:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/22 18:40:43 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned long	nbr;

	nbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + ((unsigned long)*str - 48);
		str++;
	}
	if (nbr > 2147483647 && sign == 1)
		return (-1);
	if (nbr > 2147483648 && sign == -1)
		return (0);
	return ((int)((long)nbr * sign));
}

unsigned long long	ft_atoi_unsigned_long_long(const char *str)
{
	int					sign;
	unsigned long long	nbr;
	unsigned long long	limit;

	limit = 9223372036854775807;
	nbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + ((long long)*str - 48);
		str++;
	}
	if (nbr > 9223372036854775807 && sign == 1)
		return (-1);
	if (nbr > (unsigned long long)limit + 1 && sign == -1)
		return (0);
	return ((nbr * (unsigned long long)sign));
}
