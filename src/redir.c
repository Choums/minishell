/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:28:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/20 16:54:10 by chaidel          ###   ########.fr       */
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

/*
 *	Remet a leur valeur initiale stdin, stdout et stderr s'ils ont été utilisé
 *	(Utile uniquement pour les builtins éxecutés dans le parent)
*/
void	restore_redir(t_redirection *tab)
{
	if (*(tab->in))
	{
		dup2(tab->cpy_in, 0);
		close(tab->cpy_in);
	}
	if (*(tab->out))
	{
		dup2(tab->cpy_out, 1);
		close(tab->cpy_out);
	}
}

int	close_cpy(t_redirection *tab)
{
	if (tab->cpy_in)
		close(tab->cpy_in);
	if (tab->cpy_out)
		close(tab->cpy_out);
	return (1);
}

int	redir(t_data *data, t_redirection *tab)
{
	size_t	i;

	i = 0;
	while (tab->in[i])
	{
		if (tab->token_in[i][0] == '1')
		{
			if (!in_redir(tab, tab->in[i]))
				return (0);
		}
		else
			heredoc(data, tab);
		i++;
	}
	i = 0;
	while (tab->out[i])
	{
		if (tab->token_out[i][0] == '1')
		{
			if (!out_redir(tab, tab->out[i]))
				return (0);
		}
		else
			if (!append_mode(tab, tab->out[i]))
				return (0);
		i++;
	}
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
	tab->out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tab->out_fd < 0)
		return (redir_err(file));
	tab->cpy_out = dup(1);
	close(1);
	dup2(tab->out_fd, 1);
	close(tab->out_fd);
	return (1);
}

int	in_redir(t_redirection *tab, char *file)
{

	tab->in_fd = open(file, O_RDONLY);
	if (tab->in_fd < 0)
		return (redir_err(file));
	tab->cpy_in = dup(0);
	close(0);
	dup2(tab->in_fd, 0);
	close(tab->in_fd);
	return (1);
}

/*
 *	Definis si file est un fichier ou un directory et recup son fd
 *	Return	=>	0 directory
 *				1 file
 *	-------------------------------------
 *	Appel de stat()
 *
*/
// int	opening_mode(char *pathname)
// {
// 	struct stat	path_stat;

// 	stat(pathname, &path_stat);
// 	return ();
// }

/*
 *	Redirige l'entrée et sortie du process vers le/les pipes
*/
void	redir_pipe(int *pipefd, int pos, int n_pipe)
{
	// printf("redir pipe | pos: %d\n", pos);
	if (pos == 0)
	{
		// printf("fst cmd\n");
		// printf("fd [%d]: %d \n", pos + 1, pipefd[pos+1]);
		if (dup2(pipefd[pos + 1], STDOUT_FILENO) < 0)
			perror("dup2");
		close(pipefd[pos + 1]);
		// printf("dup done\n---\n");
	}
	else if (pos == n_pipe)
	{
		// printf("lst cmd\n");
		// printf("fd [%d]: %d \n", (n_pipe * 2) - 2, pipefd[(n_pipe * 2) - 2]);
		dup2(pipefd[(n_pipe * 2) - 2], STDIN_FILENO);
		close(pipefd[(n_pipe * 2) - 2]);
		// printf("dup done\n---\n");
	}
	else
	{
		// printf("mid %d cmd\n", pos);
		// printf("fd [%d]: %d \n", (pos * 2)-2, pipefd[(pos * 2)-2]);
		// printf("fd [%d]: %d \n", (pos * 2) + 1, pipefd[(pos * 2) + 1]);
		dup2(pipefd[(pos * 2) - 2], STDIN_FILENO);
		dup2(pipefd[(pos * 2) + 1], STDOUT_FILENO);
		close(pipefd[(pos * 2) - 2]);
		close(pipefd[(pos * 2) + 1]);
		// printf("dup done\n---\n");
	}
}
