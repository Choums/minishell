/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:28:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/02 17:30:37 by chaidel          ###   ########.fr       */
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
			printf("here\n");		
		i++;
	}
	i = 0;
	while (tab->out[i])
	{
		// printf("token: %d\n", tab->token_out);
		if (tab->token_out[i][i] == '1')
		{
			printf("inout\n");
			out_redir(data, tab->out[i]);
			printf("out\n");
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
	printf("start outredir\nfile: %s: ", file);
	out_fd  = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("%d\n", out_fd);
	if (out_fd < 0)
		ft_err("Open");
	printf("start dup\n");
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		printf("echec dup ?\n");
		ft_err("Dup");
	}
	close(out_fd);
	printf("end outredir\n");
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
	in_fd = open(file, O_RDONLY);
	if (in_fd < 0)
		ft_err("Open");
	if (dup2(in_fd, STDIN_FILENO) < 0)
		ft_err("Dup");
	if (alloc)
		free(var);
}
