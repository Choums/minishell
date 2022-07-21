/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:03:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/21 19:20:35 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Copy the heredoc redirection,
 *	takes multiple lines of input until the limiter is identified.
 *	The function generates a pipe from which she passes all inputs
 *	to the current process.
 *	-------------------------
 *	Créer et ouvrir un fichier .temp
 *	Récup les inputs via gnl
 *	Écrire dans le .temp
 *	Fermer le .temp et le supp.
*/
int	heredoc(t_data *data, t_redirection *tab, char *lim)
{
	char	*line;
	char	*new_line;
	char	*end;
	int		file;

	file = open(".here", O_CREAT | O_RDWR | O_TRUNC, 0644);
	new_line = ft_calloc(1, 1);
	end = lim;
	end = ft_strjoin(end, "\n");
	while (1)
	{
		display_here();
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, end) == 0)
		{
			free(end);
			free(line);
			break ;
		}
		check_expand(data, line);
		new_line = ft_join(new_line, line);
		free(line);
	}
	ft_putstr_fd(new_line, file);
	free(new_line);
	tab->cpy_in = dup(STDIN);
	close(STDIN);
	dup2(file, STDIN);
	close(file);
	return (1);
}

void	display_here(void)
{
	char	*msg;

	msg = "> ";
	ft_putstr_fd(msg, STDIN_FILENO);
}

void	check_expand(t_data *data, char *line)
{
	if (ft_strchr(line, '$'))
	{
		line = which_dollar(data, line);
		line = ft_join(line, "\n");
	}
	return (line);
}
