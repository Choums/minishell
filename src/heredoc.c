/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:03:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/22 14:57:42 by chaidel          ###   ########.fr       */
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
 *	Écrit les saisies dans le .temp
 *	Redirige le .temp vers l'entrée
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
		line = check_expand(data, line);
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

char	*check_expand(t_data *data, char *line)
{
	if (ft_strchr(line, '$'))
	{
		line = ft_strtrim(line, "\n");
		line = which_dollar(data, line);
		line = ft_join(line, "\n");
	}
	return (line);
}
