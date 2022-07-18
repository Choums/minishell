/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:58:15 by aptive            #+#    #+#             */
/*   Updated: 2022/07/18 19:47:39 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	token_quote(t_command **t_p, int nb_pp, int i)
{
	if (ft_strchr(t_p[nb_pp]->tab_cmd[i], '\''))
		return ('4');
	else if (ft_strchr(t_p[nb_pp]->tab_cmd[i], '"'))
		return ('5');
	else
		return ('3');
}
