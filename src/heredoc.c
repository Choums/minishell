/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:03:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/24 18:30:34 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Copy the heredoc redirection,
 *	takes multiple lines of input until the limiter is identified.
 *	The function generates a pipe from which she passes all inputs
 *	to the current process.
 *	args:	1	 => cmd
 *			n	 => cmd arg
 *			last => Limiter
 *	(Display the pipes)
 *	-------------------------
 *	Créer et ouvrir un fichier .temp
 *	Écrire dedans les inputs
 *	Récup les lignes via gnl avec le fd du .temp
 *	Fermer le .temp et le supp.
*/
void	heredoc(t_data *data, char **args)
{
	char	*line;
	char	*new_line;
	char	*end;
	int		file;

	file = open(".here", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	new_line = ft_calloc(1, 1);
	end = get_lim(args);
	end = ft_strjoin(end, "\n");
	while (1)
	{
		display_here();
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, end) == 0)
		{
			free(end);
			free(line);	
			break;
		}
		if (ft_strchr(line, '$'))
		{
			line = which_dollar(data, line);
			line = ft_join(line, "\n");
		}
		new_line = ft_join(new_line, line);
		free(line);
	}
	ft_putstr_fd(new_line, file);
	free(new_line);
	// unlink(".here");
	// if (dup2(file, STDIN_FILENO) < 0)
	// 	ft_err("Dup2");
	close(file);
}

void	display_here(void)
{
	char	*msg;

	msg = "> ";
	ft_putstr_fd(msg, STDIN_FILENO);
}

char	*get_lim(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	// printf("lim: %s\n", args[i-1]);
	return (args[i - 1]);
}