/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:28:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/31 19:23:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
 *	>>
 *	Ouvre et/ou créer un ficher de sortie en mode append
 *	O_WRONLY | O_CREAT | O_APPEND, 0644
 *	args[n]		-> ">>"
 *	args[n+1]	-> fichier
*/
void	append_mode(char **args)
{
	size_t	i;
	int		out_fd;

	i = -1;
	while (ft_strcmp(args[i], ">>") != 0)
		i++;
	out_fd = open(args[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
		ft_err("Open");
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		ft_err("Dup2");
}


void	redir(t_data *data, t_redirection *tab)
{
	if (tab->token_in == 1)
		
}

/*
 *	>
 *	Ouvre et/ou créer un ficher de sortie
 *	O_WRONLY | O_CREAT O_TRUNC, 0644
 *	args[]
 *	args[n]		-> '>'
 *	args[n+1]	-> fichier
*/
// void	out_redir(t_redirection *args)
// {
// 	size_t	i;
// 	int		out_fd;

// 	i = -1;
// 	out_fd  = open(args[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (out_fd < 0)
// 		ft_err("Open");
// 	if (dup2(out_fd, STDOUT_FILENO) < 0)
// 		ft_err("Dup");
// }

void	in_redir(char **args)
{
	int		in_fd;

	in_fd = open(args[i], O_RDONLY);
	if (in_fd < 0)
		ft_err("Open");
	if (dup2(in_fd, STDIN_FILENO) < 0)
		ft_err("Dup");
}
