/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:03:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/24 13:39:00 by chaidel          ###   ########.fr       */
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
void	heredoc(char **args, int n_pipe)
{
	char	*line;
	char	*end;
	// int		fd[2];
	int		file;

	// if (pipe(fd) == -1)
	// 	ft_err("Pipe");
	file = open(".here", O_CREAT | O_WRONLY, 0644);
	line = malloc(sizeof(char));
	end = get_lim(args);
	end = ft_strjoin(end, "\n");
	while (ft_strcmp(line, end) != 0)
	{
		free(line);
		display_here(n_pipe);
		line = get_next_line(file);
		ft_putstr_fd(line, file);
		printf("l:%s\ne:%s\n", line, end);
	}
	free(line);
	unlink(".here");
	// if (dup2(fd[0], STDIN_FILENO) == -1)
	// 	ft_err("Dup2");
	// close(fd[0]);
	// close(fd[1]);
}

// int	temp_here(char **args)
// {
// 	int	fd;
// 	char	*line;
	
// 	fd = open(".here", O_CREAT | O_WRONLY, 0644);
	
// 	line = get_next_line(STDIN_FILENO);
// 	ft_putstr_fd(line, fd);
// 	return (fd);
// 	// sleep(30);
// 	// unlink(".here");
// }

void	display_here(int n_pipe)
{
	char	*msg;

	msg = "heredoc> ";
	if (n_pipe == 1)
	{
		ft_putstr_fd(msg, STDIN_FILENO);
		return ;
	}
	while (--n_pipe)
		msg = ft_strjoin("pipe ", msg);
	ft_putstr_fd(msg, STDIN_FILENO);
	printf("out display\n");
}

char	*get_lim(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	printf("lim: %s\n", args[i-1]);
	return (args[i - 1]);
}