/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:28:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/24 13:22:22 by chaidel          ###   ########.fr       */
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
}


/*
 *	>
 *	Ouvre et/ou créer un ficher de sortie
 *	O_WRONLY | O_CREAT O_TRUNC, 0644
 *	args[]
 *	args[n]		-> '>'
 *	args[n+1]	-> fichier
*/
void	out_redir(char **args)
{
	size_t	i;
	int		out_fd;

	i = -1;
	while (ft_strcmp(args[i], ">") != 0)
		i++;
	out_fd  = open(args[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
		ft_err("Open");
}

void	in_redir(char **args)
{
	size_t	i;
	int		in_fd;

	i = -1;
	while (ft_strcmp(args[i], "<") != 0)
		i++;
	in_fd = open(args[i], O_RDONLY);
	if (in_fd < 0)
		ft_err(Open);
}