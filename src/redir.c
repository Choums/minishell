/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:28:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/14 18:52:04 by root             ###   ########.fr       */
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
		ft_err("Open");
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
	out_fd  = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
		ft_err("Open");
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		ft_err("Dup");
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
	struct stat path_stat;
	stat(pathname, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

/*
 *	Redirige l'entrée et sortie du process vers le/les pipes
*/
void	redir_pipe(int pipefd[][2], int pos, int n_pipe)
{
	if (pos == 0)
	{
		fprintf(stderr, "fst cmd\n");
		dup2(pipefd[pos][1], STDOUT_FILENO);
	}
	else if (pos == n_pipe - 1)
	{
		fprintf(stderr, "lst cmd\n");
		dup2(pipefd[pos - 1][0], STDIN_FILENO);
	}
	else
	{
		fprintf(stderr, "mid %d cmd\n", pos);
		dup2(pipefd[pos - 1][0], STDIN_FILENO);
		dup2(pipefd[pos][1], STDOUT_FILENO);
	}
}
