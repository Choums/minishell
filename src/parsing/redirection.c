/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:08:18 by aptive            #+#    #+#             */
/*   Updated: 2022/07/19 16:10:30 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	init_redir_zero(table_pipe, number_pipe);
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
	nb_redirect = ft_count_redirection(table_pp[nb_pp]->all_pipe, c);
	tmp = table_pp[nb_pp]->all_pipe;
	// printf("tmp : %s\n", tmp);
	while (nb_redirect)
	{
		cut = 0;
		dex = 0;
		tmp = ft_search_redir(tmp, c);
		while (tmp[dex] == c || tmp[dex] == ' ')
			dex++;
		// printf("tmp[dex] : %c\n", tmp[dex]);
		if (tmp[dex] == '"' || tmp[dex] == '\'')
			cut += pass_quote_verif_line(tmp, dex);
		while ((tmp[dex + cut] != ' ' && tmp[dex + cut] != '<'
				&& tmp[dex + cut] != '>') && tmp[dex + cut])
		{
				cut++;
		}
		table_pp[nb_pp]->tab_redir->in[i] = ft_substr(tmp, dex, cut);
		// printf("table_pp[%i]->tab_redir->in[%i] = %s\n",nb_pp, i, table_pp[nb_pp]->tab_redir->in[i]);
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
		j = 1;
		if (str[i] == '\'' || str[i] == '"')
		{
			while (str[i + j] && str[i + j] != str[i])
				j++;
			j++;
		}
		else if (str[i] == c)
			return (str + i + j);
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
	tmp = table_pp[nb_pp]->all_pipe;
	while (nb_redirect)
	{
		cut = 0;
		dex = 0;
		tmp = ft_search_redir(tmp, c);
		while (tmp[dex] == c || tmp[dex] == ' ')
			dex++;
		if (tmp[dex] == '"' || tmp[dex] == '\'')
			cut += pass_quote_verif_line(tmp, dex);
		while ((tmp[dex + cut] != ' ' && tmp[dex + cut] != '<'
				&& tmp[dex + cut] != '>') && tmp[dex + cut])
			cut++;
		table_pp[nb_pp]->tab_redir->out[i] = ft_substr(tmp, dex, cut);
		tmp = tmp + dex;
		nb_redirect--;
		i++;
	}
}
