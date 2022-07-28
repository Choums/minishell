/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:28:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/28 16:38:50 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Remet a leur valeur initiale stdin, stdout et stderr s'ils ont été utilisé
 *	(Utile uniquement pour les builtins éxecutés dans le parent)
*/
void	restore_redir(t_redirection *tab)
{
	restore_in(tab);
	restore_out(tab);
	unlink(".here");
}

int	restore_in(t_redirection *tab)
{
	if (tab->cpy_in)
	{
		dup2(tab->cpy_in, STDIN);
		close(tab->cpy_in);
	}
	unlink(".here");
	return (1);
}

int	restore_out(t_redirection *tab)
{
	if (tab->cpy_out)
	{
		dup2(tab->cpy_out, STDOUT);
		close(tab->cpy_out);
	}
	return (1);
}

int	close_cpy(t_redirection *tab)
{
	if (tab->cpy_in)
		close(tab->cpy_in);
	if (tab->cpy_out)
		close(tab->cpy_out);
	return (1);
}

/*
 *	Redirige l'entrée et sortie du process vers le/les pipes
*/
void	redir_pipe(int *pipefd, int pos, int n_pipe)
{
	if (pos == 0)
		dup2(pipefd[pos + 1], STDOUT_FILENO);
	else if (pos == n_pipe)
		dup2(pipefd[(n_pipe * 2) - 2], STDIN_FILENO);
	else
	{
		dup2(pipefd[(pos * 2) - 2], STDIN_FILENO);
		dup2(pipefd[(pos * 2) + 1], STDOUT_FILENO);
	}
}
