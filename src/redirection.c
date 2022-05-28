/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:08:18 by aptive            #+#    #+#             */
/*   Updated: 2022/05/28 02:23:19 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_redirection(char *str, char c_redirect)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c_redirect)
		{
			if (str[++i])
				count++;
			else
				count++;
		}
	}
	return (count);
}

t_command	**ft_redirection_init(t_command	*(*table_pipe), int number_pipe)
{
	int	nb_pipe_in;
	int	nb_pipe_out;

	nb_pipe_in = ft_count_redirection(table_pipe[number_pipe]->all_pipe, '<');
	nb_pipe_out = ft_count_redirection(table_pipe[number_pipe]->all_pipe, '>');
	table_pipe[number_pipe]->tab_redirection = malloc(sizeof(t_redirection));
	if (!nb_pipe_in && !nb_pipe_out)
	{
		table_pipe[number_pipe]->tab_redirection = NULL;
		return (table_pipe);
	}
	table_pipe[number_pipe]->tab_redirection->in
		= malloc(sizeof(char **) * (nb_pipe_in + 1));
	if (!table_pipe[number_pipe]->tab_redirection->in)
		return (NULL);
	table_pipe[number_pipe]->tab_redirection->in[nb_pipe_in] = NULL;
	table_pipe[number_pipe]->tab_redirection->out
		= malloc(sizeof(char **) * (nb_pipe_out + 1));
	if (!table_pipe[number_pipe]->tab_redirection->out)
		return (NULL);
	table_pipe[number_pipe]->tab_redirection->out[nb_pipe_out] = NULL;
	return (table_pipe);
}

t_command	**ft_parse_redirection_in(t_command	*(*table_pipe), int	number_pipe, char c_redirect)
{
	char	*tmp;
	int		to_cut;
	int		index;
	int		i;
	int		nb_redirect;

	i = 0;
	table_pipe = ft_redirection_init(table_pipe, number_pipe);
	nb_redirect = ft_count_redirection(table_pipe[number_pipe]->all_pipe, c_redirect);
	tmp = table_pipe[number_pipe]->all_pipe;
	while (nb_redirect)
	{
		to_cut = 0;
		index = 0;
		tmp = ft_strchr(tmp, c_redirect);
		while (tmp[index] == c_redirect || tmp[index] == ' ')
			index++;
		while ((tmp[index + to_cut] != ' ' && tmp[index + to_cut] != c_redirect) && tmp[index + to_cut])
			to_cut++;
		if (c_redirect == '<')
			table_pipe[number_pipe]->tab_redirection->in[i] = ft_substr(tmp, index, to_cut);
		else
			table_pipe[number_pipe]->tab_redirection->out[i] = ft_substr(tmp, index, to_cut);
		tmp = tmp + index;
		nb_redirect--;
		i++;
	}
	return(table_pipe);
}

t_command	**ft_parse_redirection_out(t_command	*(*table_pipe), int	number_pipe, char c_redirect)
{
	char	*tmp;
	int		to_cut;
	int		index;
	int		i;
	int		nb_redirect;

	i = 0;
	nb_redirect = ft_count_redirection(table_pipe[number_pipe]->all_pipe, c_redirect);
	tmp = table_pipe[number_pipe]->all_pipe;
	while (nb_redirect)
	{
		to_cut = 0;
		index = 0;
		tmp = ft_strchr(tmp, c_redirect);
		while (tmp[index] == c_redirect || tmp[index] == ' ')
			index++;
		while ((tmp[index + to_cut] != ' ' && tmp[index + to_cut] != c_redirect) && tmp[index + to_cut])
			to_cut++;
		if (c_redirect == '<')
			table_pipe[number_pipe]->tab_redirection->in[i] = ft_substr(tmp, index, to_cut);
		else
			table_pipe[number_pipe]->tab_redirection->out[i] = ft_substr(tmp, index, to_cut);
		tmp = tmp + index;
		nb_redirect--;
		i++;
	}
	return(table_pipe);
}
