/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:17:59 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/27 21:05:36 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir(t_data *data, t_redirection *tab)
{
	int	i;

	i = -1;
	while (tab->tab_fusion[++i])
	{
		if (tab->tab_fusion_to[i][0] == '1')
		{
			if (restore_in(tab) && !in_redir(tab, tab->tab_fusion[i]))
				return (0);
		}
		else if (tab->tab_fusion_to[i][0] == '2')
		{
			if (restore_in(tab) && !heredoc(data, tab, tab->tab_fusion[i]))
				return (0);
		}
		else if (!redir_sc(tab, i))
			return (0);
	}
	return (1);
}

int	redir_sc(t_redirection *tab, int i)
{
	if (tab->tab_fusion_to[i][0] == '3')
	{
		if (restore_out(tab) && !out_redir(tab, tab->tab_fusion[i]))
			return (0);
	}
	else
		if (restore_out(tab) && !append_mode(tab, tab->tab_fusion[i]))
			return (0);
	return (1);
}

/*
 *	>
 *	Ouvre et/ou créer un ficher de sortie
 *	O_WRONLY | O_CREAT O_TRUNC, 0644
 *	args[]
 *	args[n]		-> '>'
 *	args[n+1]	-> fichier
*/
int	out_redir(t_redirection *tab, char *file)
{
	if (file == NULL)
	{
		ft_putendl_fd("minishell: ambiguous redirect", STDERR);
		return (0);
	}
	tab->out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tab->out_fd < 0)
		return (redir_err(file));
	make_cpy_out(tab);
	dup2(tab->out_fd, 1);
	close(tab->out_fd);
	return (1);
}

int	in_redir(t_redirection *tab, char *file)
{
	if (file == NULL)
	{
		ft_putendl_fd("minishell: ambiguous redirect", STDERR);
		return (0);
	}
	tab->in_fd = open(file, O_RDONLY);
	if (tab->in_fd < 0)
		return (redir_err(file));
	tab->cpy_in = dup(0);
	make_cpy_in(tab);
	close(tab->in_fd);
	return (1);
}

/*
 *	>>
 *	Ouvre et/ou créer un ficher de sortie en mode append
 *	O_WRONLY | O_CREAT | O_APPEND, 0644
 *	args[n]		-> ">>"
 *	args[n+1]	-> fichier
*/
int	append_mode(t_redirection *tab, char *file)
{
	tab->out_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tab->out_fd < 0)
		return (redir_err(file));
	tab->cpy_out = dup(1);
	close(1);
	dup2(tab->out_fd, 1);
	close(tab->out_fd);
	return (1);
}
