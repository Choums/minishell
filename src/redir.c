/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:28:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/17 20:20:53 by root             ###   ########.fr       */
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
void	append_mode(t_data *data, char *file)
{
	int		out_fd;
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
	out_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
		perror("Open");
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		ft_err("Dup2");
	if (alloc)
		free(var);
}


void	redir(t_data *data, t_redirection *tab)
{
	size_t	i;

	i = 0;
	while (tab->in[i])
	{
		if (tab->token_in[i][i] == '1')
			in_redir(data, tab->in[i]);
		else
			heredoc(data, tab);
		i++;
	}
	i = 0;
	while (tab->out[i])
	{
		// printf("token: %d\n", tab->token_out);
		if (tab->token_out[i][i] == '1')
		{
			// printf("inout\n");
			out_redir(data, tab->out[i]);
			// printf("out\n");
		}
		else
			append_mode(data, tab->out[i]);
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
void	out_redir(t_data *data, char *file)
{
	int		out_fd;
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
	out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
		perror("Open");
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		perror("Dup");
	close(out_fd);
	if (alloc)
		free(var);
}

void	in_redir(t_data *data, char *file)
{
	int		in_fd;
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
	printf("type: %d\n", opening_mode(file));
	in_fd = open(file, O_RDONLY);
	// if (in_fd < 0)
	// 	ft_err("Open");
	if (dup2(in_fd, STDIN_FILENO) < 0)
		// ft_err("Dup");
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
int	opening_mode(char *pathname)
{
	struct stat	path_stat;

	stat(pathname, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

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
		// printf("dup done\n---\n");
	}
	else if (pos == n_pipe)
	{
		// printf("lst cmd\n");
		// printf("fd [%d]: %d \n", (n_pipe * 2) - 2, pipefd[(n_pipe * 2) - 2]);
		dup2(pipefd[(n_pipe * 2) - 2], STDIN_FILENO);
		// printf("dup done\n---\n");
	}
	else
	{
		// printf("mid %d cmd\n", pos);
		// printf("fd [%d]: %d \n", (pos * 2)-2, pipefd[(pos * 2)-2]);
		// printf("fd [%d]: %d \n", (pos * 2) + 1, pipefd[(pos * 2) + 1]);
		dup2(pipefd[(pos * 2) - 2], STDIN_FILENO);
		dup2(pipefd[(pos * 2) + 1], STDOUT_FILENO);
		// printf("dup done\n---\n");
	}
}
