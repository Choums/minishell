/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:46:05 by chaidel           #+#    #+#             */
/*   Updated: 2021/11/28 17:06:07 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*tmp_s;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	tmp_s = ft_strdup(s);
	if (!tmp_s)
		return (NULL);
	while (s[i])
	{
		tmp_s[i] = (*f)(i, s[i]);
		i++;
	}
	return (tmp_s);
}
