/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:33:32 by tdelauna          #+#    #+#             */
/*   Updated: 2022/06/13 17:22:20 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	verif_quote(char *line)
// {
// 	int	i;
// 	int	nb_quote;

// 	i = 0;
// 	nb_quote = 0;
// 	while (i < ft_strlen(line))
// 	{
// 		if (line[i] == '\'')
// 		{
// 			nb_quote++;
// 			i++;
// 			while (line[i] && line[i] != '\'')
// 				i++;
// 			if (line[i] == '\'')
// 				nb_quote++;
// 		}
// 		if (line[i] == '"')
// 		{
// 			nb_quote++;
// 			i++;
// 			while (line[i] && line[i] != '"')
// 				i++;
// 			if (line[i] == '"')
// 				nb_quote++;
// 		}
// 		i++;
// 	}
// 	if (nb_quote % 2)
// 	{
// 		ft_putstr_fd("Error : unclosed quotation mark\n", STDERR);
// 		return (0);
// 	}
// 	return (1);
// }

int	verif_quote(char *line)
{
	int	i;
	int	j;
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (i < ft_strlen(line))
	{
		j = 1;
		if (line[i] == '\'' || line[i] == '"')
		{
			nb_quote++;
			while (line[i + j] && line[i + j] != line[i])
				j++;
			if (line[i + j++] == line[i])
				nb_quote++;
		}
		i += j;
	}
	if (nb_quote % 2)
	{
		ft_putstr_fd("Error : unclosed quotation mark\n", STDERR);
		return (0);
	}
	return (1);
}

int	verif_line(char *line)
{
	if (line && ft_strlen(line) && verif_quote(line))
		return (1);
	else
		return (0);
}
