/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:08:09 by aptive            #+#    #+#             */
/*   Updated: 2022/06/26 16:27:53 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	verif_quote(char *line)
// {
// 	int	i;
// 	int	j;
// 	int	nb_quote;

// 	i = 0;
// 	nb_quote = 0;
// 	while (i < ft_strlen(line))
// 	{
// 		j = 1;
// 		if (line[i] == '\'' || line[i] == '"')
// 		{
// 			nb_quote++;
// 			while (line[i + j] && line[i + j] != line[i])
// 				j++;
// 			if (line[i + j++] == line[i])
// 				nb_quote++;
// 		}
// 		i += j;
// 	}
// 	if (nb_quote % 2)
// 	{
// 		ft_putstr_fd("Error : unclosed quotation mark\n", STDERR);
// 		return (0);
// 	}
// 	return (1);
// }

static int	count_pipe(char *line)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 1;
	while (i < ft_strlen(line))
	{
		j = 1;
		if (line[i] == '\'' || line[i] == '"')
		{
			while (line[i + j] && line[i + j] != line[i])
			{
				if (line[i + j] == '\\')
					j += 2;
				j++;
			}
			j++;
		}
		else if (line[i] == '|')
			count++;
		i += j;
	}
	return (count);
}

static	void	ft_get_to_next_pipe(char **str, int *len)
{
	int	i;

	*str = *str + *len;
	while (**str == '|' && **str)
		(*str)++;
	*len = 0;
	while ((*str)[*len] != '|' && (*str)[*len])
	{
		if ((*str)[*len] == '\'' || (*str)[*len] == '"')
		{
			i = *len;
			(*len)++;
			while ((*str)[*len] != (*str)[i])
			{
				if((*str)[*len] == '\\')
					(*len) += 2;
				else
					(*len)++;
			}
		}
		(*len)++;
	}
}

char	**split_pipe(char *s)
{
	char	**split;
	char	*tmp_s;
	int		word_len;
	size_t	num;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	word_len = 0;
	tmp_s = (char *)s;
	num = count_pipe(tmp_s);
	split = (char **)malloc(sizeof(char *) * (num + 1));
	if (!split)
		return (NULL);
	split[num] = NULL;
	while (i < num)
	{
		ft_get_to_next_pipe(&tmp_s, &word_len);
		split[i] = (char *)malloc(sizeof(char) * (word_len + 1));
		ft_strlcpy(split[i], tmp_s, word_len + 1);
		i++;
	}
	return (split);
}
