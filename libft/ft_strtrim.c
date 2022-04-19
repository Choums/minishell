/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:25:51 by chaidel           #+#    #+#             */
/*   Updated: 2021/12/04 17:19:02 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_sep(char c, char const *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *sep)
{
	unsigned int		start;
	size_t				end;
	char				*trim;
	size_t				i;

	i = 0;
	start = 0;
	end = 0;
	if (!str)
		return (NULL);
	while (is_sep(str[i++], sep))
		start++;
	i = ft_strlen(str) - 1;
	while (is_sep(str[i], sep) && i)
	{
		end++;
		i--;
	}
	if (start == ft_strlen(str))
		return (trim = ft_strdup(""));
	trim = ft_substr(str, start, ft_strlen(str) - end - start);
	if (!trim)
		return (NULL);
	return (trim);
}
