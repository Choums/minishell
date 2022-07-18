/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:38:11 by tdelauna          #+#    #+#             */
/*   Updated: 2022/07/18 19:53:58 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*put_dollar(t_data *data, char *expand, char *str, int *i)
{
	char	*tmp;
	char	*tmp_str;
	int		j;

	j = *i;
	tmp_str = ft_substr(str, j, count_var (str + j));
	tmp = which_dollar(data, tmp_str);
	if (tmp)
		expand = ft_join(expand, tmp);
	free(tmp);
	free(tmp_str);
	*i += count_var (str + *i);
	return (expand);
}

char	*sexp(t_data *data, char *str)
{
	int		i;
	char	*expand;
	char	*tmp;

	expand = NULL;
	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			tmp = ft_itoa(g_signal.status);
			expand = ft_join(expand, tmp);
			free(tmp);
			i += 2;
		}
		else if (str[i] == '$'
			&& (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '"'))
			expand = ft_straddc(expand, str[i++]);
		else if (str[i] != '$')
			expand = ft_straddc(expand, str[i++]);
		else
			expand = put_dollar(data, expand, str, &i);
	}
	return (free(str), expand);
}

char	**check_linear_tab(char **tab, int len_tab)
{
	int		i;
	int		j;
	int		count;
	char	**tmp_str;

	count = linear_check_tab(tab, len_tab);
	j = 0;
	i = 0;
	if (count)
	{
		tmp_str = malloc(sizeof(char *) * (len_tab - count + 1));
		if (!tmp_str)
			return (NULL);
		tmp_str[len_tab - count] = NULL;
		while (i < len_tab)
		{
			if (!tab[i])
				i++;
			else
				tmp_str[j++] = tab[i++];
		}
		return (free(tab), tmp_str);
	}
	return (tab);
}

void	go_expand(t_data *data, t_command *(*tp))
{
	int	i;
	int	j;

	i = -1;
	while (tp[++i])
	{
		j = -1;
		while (tp[i]->tab_cmd[++j])
			if (ft_strchr(tp[i]->tab_cmd[j], '$')
				&& tp[i]->tab_token[j][0] != '4')
				tp[i]->tab_cmd[j] = sexp(data, tp[i]->tab_cmd[j]);
		tp[i]->tab_cmd = check_linear_tab(tp[i]->tab_cmd, j);
		j = -1;
		while (tp[i]->tab_redir && tp[i]->tab_redir->out[++j])
			if (tp[i]->tab_redir->out[j][0] != '\'')
				tp[i]->tab_redir->out[j] = sexp(data, tp[i]->tab_redir->out[j]);
		if (tp[i]->tab_redir && tp[i]->tab_redir->out)
			tp[i]->tab_redir->out = check_linear_tab(tp[i]->tab_redir->out, j);
		j = -1;
		while (tp[i]->tab_redir && tp[i]->tab_redir->in[++j])
			if (tp[i]->tab_redir->in[j][0] != '\'')
				tp[i]->tab_redir->in[j] = sexp(data, tp[i]->tab_redir->in[j]);
		if (tp[i]->tab_redir && tp[i]->tab_redir->out)
			tp[i]->tab_redir->in = check_linear_tab(tp[i]->tab_redir->in, j);
	}
}
