/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:25:07 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/16 00:42:30 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_free_tab(char **split, size_t i)
{
	while (i)
	{
		free(split[i]);
		i--;
	}
	free(split);
	return (NULL);
}

static	size_t	ft_count_words(char *str, char sep)
{
	size_t	count;

	count = 0;
	while (*str == sep && *str)
		str++;
	while (*str)
	{
		count++;
		while (*str != sep && *str)
			str++;
		while (*str == sep && *str)
			str++;
	}
	return (count);
}

static	void	ft_get_to_next_word(char **str, char sep, size_t *len)
{
	*str = *str + *len;
	while (**str == sep && **str)
		(*str)++;
	*len = 0;
	while ((*str)[*len] != sep && (*str)[*len])
		(*len)++;
}

char	**ft_split(char const *s, char sep)
{
	char	**split;
	char	*tmp_s;
	size_t	word_len;
	size_t	num;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	word_len = 0;
	tmp_s = (char *)s;
	num = ft_count_words(tmp_s, sep);
	split = (char **)malloc(sizeof(char *) * (num + 1));
	if (!split)
		return (NULL);
	split[num] = NULL;
	while (i < num)
	{
		ft_get_to_next_word(&tmp_s, sep, &word_len);
		split[i] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!split[i])
			return (ft_free_tab(split, i));
		ft_strlcpy(split[i++], tmp_s, word_len + 1);
	}
	return (split);
}
