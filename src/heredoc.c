/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:03:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/21 17:43:27 by chaidel          ###   ########.fr       */
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
*/
void	heredoc(char **args, int n_pipe)
{
	char	*line;
	char	*end;
	char	*new_line;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_err("Pipe");
	line = "\0";
	new_line = line;
	end = get_lim(args);
	end = ft_strjoin(end, "\n");
	while (ft_strcmp(line, end) != 0)
	{
		display_here(n_pipe);
		line = get_next_line(STDIN_FILENO);
		new_line = ft_join(new_line, line);
	}
	free(line);
	if (write(fd[1], new_line, ft_strlen(new_line)) == -1)
		ft_err("Write");
	free(new_line);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_err("Dup2");
	close(fd[0]);
	close(fd[1]);
}

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