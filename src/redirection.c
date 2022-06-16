/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:08:18 by aptive            #+#    #+#             */
/*   Updated: 2022/06/16 03:12:34 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_redirection(char *str, char c_redirect)
{
	int	i;
	int	count;
	int	j;

	i = -1;
	count = 0;
	while (i < ft_strlen(str))
	{
		j = 1;
		if (str[i] == '\'' || str[i] == '"')
		{
			while (str[i + j] && str[i + j] != str[i])
				j++;
			j++;
		}
		else if (str[i] == c_redirect)
		{
			if (str[++i])
				count++;
			else
				count++;
		}
		i += j;
	}
	return (count);
}

t_command	**ft_redirection_init(t_command	*(*table_pipe), int number_pipe)
{
	int	nb_pipe_in;
	int	nb_pipe_out;

	nb_pipe_in = ft_count_redirection(table_pipe[number_pipe]->all_pipe, '<');
	nb_pipe_out = ft_count_redirection(table_pipe[number_pipe]->all_pipe, '>');
	table_pipe[number_pipe]->tab_redir = malloc(sizeof(t_redirection));
	if (!nb_pipe_in && !nb_pipe_out)
	{
		table_pipe[number_pipe]->tab_redir = NULL;
		return (table_pipe);
	}
	table_pipe[number_pipe]->tab_redir->in
		= malloc(sizeof(char **) * (nb_pipe_in + 1));
	if (!table_pipe[number_pipe]->tab_redir->in)
		return (NULL);
	table_pipe[number_pipe]->tab_redir->in[nb_pipe_in] = NULL;
	table_pipe[number_pipe]->tab_redir->out
		= malloc(sizeof(char **) * (nb_pipe_out + 1));
	if (!table_pipe[number_pipe]->tab_redir->out)
		return (NULL);
	table_pipe[number_pipe]->tab_redir->out[nb_pipe_out] = NULL;
	return (table_pipe);
}

void	ft_parse_redir_in(t_command *(*table_pp), int nb_pp, char c)
{
	char	*tmp;
	int		cut;
	int		dex;
	int		i;
	int		nb_redirect;

	i = 0;
	table_pp = ft_redirection_init(table_pp, nb_pp);
	nb_redirect = ft_count_redirection(table_pp[nb_pp]->all_pipe, c);
	tmp = table_pp[nb_pp]->all_pipe;
	while (nb_redirect)
	{
		cut = 0;
		dex = 0;
		tmp = ft_strchr(tmp, c);
		while (tmp[dex] == c || tmp[dex] == ' ')
			dex++;
		while (tmp[dex + cut] != ' ' && tmp[dex + cut] != c && tmp[dex + cut])
			cut++;
		table_pp[nb_pp]->tab_redir->in[i] = ft_substr(tmp, dex, cut);
		tmp = tmp + dex;
		nb_redirect--;
		i++;
	}
}

char	*ft_search_redir(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == '\'' || str[i] == '"')
		{
			while (str[i + j] && str[i + j] != str[i])
				j++;
			j++;
		}
		else if (str[i] == c)
			return(str + i + j);
		i += j;
	}
	return (str + i);
}

void	ft_parse_redir_out(t_command *(*table_pp), int nb_pp, char c)
{
	char	*tmp;
	int		cut;
	int		dex;
	int		i;
	int		nb_redirect;

	i = 0;
	nb_redirect = ft_count_redirection(table_pp[nb_pp]->all_pipe, c);
	printf("nb_redirect : %i\n", nb_redirect);
	tmp = table_pp[nb_pp]->all_pipe;
	while (nb_redirect)
	{
		cut = 0;
		dex = 0;
		tmp = ft_search_redir(tmp, c);
		// tmp = ft_strchr(tmp, c);
		while (tmp[dex] == c || tmp[dex] == ' ')
			dex++;
		while ((tmp[dex + cut] != ' ' && tmp[dex + cut] != c) && tmp[dex + cut])
			cut++;
		table_pp[nb_pp]->tab_redir->out[i] = ft_substr(tmp, dex, cut);
		tmp = tmp + dex;
		nb_redirect--;
		i++;
	}
}
