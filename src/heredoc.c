/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:03:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/19 17:57:26 by aptive           ###   ########.fr       */
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
void	heredoc(t_data *data, t_redirection *args)
{
	char	*line;
	char	*new_line;
	char	*end;
	int		file;

	file = open(".here", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		return;
	new_line = ft_calloc(1, 1);
	end = args->in[0];
	end = ft_strjoin(end, "\n");
	while (1)
	{
		display_here();
		line = get_next_line(STDIN_FILENO);
		// printf("line : %s\n", line);
		if(!line)
		{
			free(end);
			break;
		}
		if (ft_strcmp(line, end) == 0)
		{
			free(end);
			free(line);
			break ;
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
	// if (dup2(file, STDIN_FILENO) < 0)
	// 	ft_err("Dup2");
	// unlink(".here");
	close(file);
}

void	display_here(void)
{
	char	*msg;

	msg = "> ";
	ft_putstr_fd(msg, STDIN_FILENO);
}
