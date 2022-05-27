/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:54:45 by aptive            #+#    #+#             */
/*   Updated: 2022/05/27 20:02:21 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	**ft_parse_cmd(t_command	*(*table_pipe), int	number_pipe)
{
	char *tmp;

	tmp = table_pipe[number_pipe]->all_pipe;
	printf("tmp : %s\n", tmp);
	return (table_pipe);
}
