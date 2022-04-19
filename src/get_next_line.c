/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:49:54 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/19 15:50:21 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_extract(int fd, char *rest)
{
	char	*brut;
	int		ret;

	ret = 1;
	brut = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!brut)
		return (NULL);
	while (!ft_chr(rest, '\n') && ret)
	{
		ret = read(fd, brut, BUFFER_SIZE);
		if (ret == -1)
		{
			free(brut);
			return (NULL);
		}
		brut[ret] = '\0';
		rest = ft_join(rest, brut);
	}
	free(brut);
	return (rest);
}

char	*ft_get_line(char *rest)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (!rest[len])
		return (NULL);
	while (rest[len] != '\n' && rest[len])
		len++;
	if (rest[len] == '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = rest[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_cut(char *rest)
{
	size_t	pos;
	size_t	i;
	char	*cut;

	i = 0;
	pos = 0;
	while (rest[pos] != '\n' && rest[pos])
		pos++;
	if (!rest[pos])
	{
		free(rest);
		return (NULL);
	}
	cut = (char *)malloc(sizeof(char) * (ft_strlen(rest) - pos + 1));
	if (!cut)
		return (NULL);
	pos++;
	while (rest[pos])
		cut[i++] = rest[pos++];
	cut[i] = '\0';
	free(rest);
	return (cut);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	rest = ft_extract(fd, rest);
	if (!rest)
		return (NULL);
	line = ft_get_line(rest);
	rest = ft_cut(rest);
	return (line);
}