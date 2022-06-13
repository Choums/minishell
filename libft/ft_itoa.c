/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:33:23 by chaidel           #+#    #+#             */
/*   Updated: 2021/12/15 18:13:36 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_negative(int *sign, int *number)
{
	*sign = 1;
	*number = -(*number);
}

static int	ft_get_len(int number)
{
	int	len;

	len = 0;
	while (number > 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

static	void	ft_set(int sign, int *len, char *str, int number)
{
	while (--(*len) >= sign)
	{
		str[*len] = (number % 10) + '0';
		number /= 10;
	}
}

char	*ft_itoa(int number)
{
	int		sign;
	int		len;
	char	*str;

	sign = 0;
	if (number == 0)
		return (ft_strdup("0"));
	if (number == -2147483648)
		return (ft_strdup("-2147483648"));
	if (number < 0)
	{
		len = ft_get_len(-number) + 1;
		ft_negative(&sign, &number);
	}
	else
		len = ft_get_len(number);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_set(sign, &len, str, number);
	if (sign)
		str[len] = '-';
	return (str);
}
