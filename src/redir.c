/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:28:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/19 18:26:33 by aptive           ###   ########.fr       */
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
void	append_mode(t_data *data, t_redirection *tab, char *file)
{
	int		alloc;
	char	*var;

	alloc = 0;
	if (ft_strchr(file, '$'))
	{
		var = which_dollar(data, file);
		alloc = 1;
		if (var == NULL)
		{
			free(var);
			ft_err("ambiguous redirect");
		}
	}
	tab->out_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tab->out_fd < 0)
	{
		g_signal.status = 1;
		// printf("Status 1: %i\n", g_signal.status);
		perror("Open");
	}
	redirect(tab);
	close(tab->out_fd);
	if (alloc)
		free(var);
}

/*
 *	Remet a leur valeur initiale stdin, stdout et stderr s'ils ont été utilisé
 *	(Utile uniquement pour les builtins éxecutés dans le parent)
*/
void	restore_redir(t_redirection *tab)
{
	if (*(tab->in))
	{
		// fprintf(stderr, "in\n");
		dup2(tab->cpy_in, 0);
		close(tab->cpy_in);
	}
	if (*(tab->out))
	{
		// fprintf(stderr, "out\n");
		dup2(tab->cpy_out, 1);
		close(tab->cpy_out);
	}
}

void	redirect(t_redirection *tab)
{
	if (*(tab->in))
	{
		tab->cpy_in = dup(STDIN_FILENO);
		dup2(tab->in_fd, STDIN_FILENO);
		close(tab->in_fd);
	}
	if (*(tab->out))
	{
		tab->cpy_out = dup(STDOUT_FILENO);
		dup2(tab->out_fd, STDOUT_FILENO);
		close(tab->out_fd);
	}
}

void	redir(t_data *data, t_redirection *tab)
{
	size_t	i;

	i = 0;
	while (tab->in[i])
	{
		if (tab->token_in[i][0] == '1')
			in_redir(data, tab, tab->in[i]);
		else
			heredoc(data, tab);
		i++;
	}
	i = 0;
	while (tab->out[i] && g_signal.status == 0)
	{
		// printf("file n%zu: %s\t| ", i, tab->out[i]);
		// printf("token: %s\n", tab->token_out[i]);
		if (tab->token_out[i][0] == '1')
		{
			// printf("inout\n");
			out_redir(data, tab, tab->out[i]);
			// printf("out\n");
		}
		else
		{
			append_mode(data, tab, tab->out[i]);
			printf("Status : %i\n", g_signal.status);

		}
		i++;
	}
}

/*
 *	>
 *	Ouvre et/ou créer un ficher de sortie
 *	O_WRONLY | O_CREAT O_TRUNC, 0644
 *	args[]
 *	args[n]		-> '>'
 *	args[n+1]	-> fichier
*/
void	out_redir(t_data *data, t_redirection *tab, char *file)
{
	int		alloc;
	char	*var;

	alloc = 0;
	if (ft_strchr(file, '$'))
	{
		var = which_dollar(data, file);
		alloc = 1;
		if (var == NULL)
		{
			free(var);
			ft_err("ambiguous redirect");
		}
	}
	tab->out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tab->out_fd < 0)
		perror("Open");
	redirect(tab);
	if (alloc)
		free(var);
}

void	in_redir(t_data *data, t_redirection *tab, char *file)
{
	int		alloc;
	char	*var;

	alloc = 0;
	if (ft_strchr(file, '$'))
	{
		var = which_dollar(data, file);
		alloc = 1;
		if (var == NULL)
		{
			free(var);
			ft_err("ambiguous redirect");
		}
	}
	tab->in_fd = open(file, O_RDONLY);
	if (tab->in_fd < 0)
		ft_err(file);
	redirect(tab);
	if (alloc)
		free(var);
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
