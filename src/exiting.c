/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:47:01 by root              #+#    #+#             */
/*   Updated: 2022/06/26 15:52:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit(t_data *data, t_command **tab, char **args)
{
	int	i;

	if (!args[1])
		is_exit(data, tab);
	check_exit_args(args);
}

/*
 *
*/
void	check_exit_args(char **args)
{

}

int	is_exit(t_data *data, t_command **tab)
{

	rl_clear_history();
	ft_lstclear(&data->env, del);
	ft_lstclear(&data->var, del);
	ft_lstclear(&data->path, del);
	free_struc(tab);
	exit(EXIT_SUCCESS);
	return (1);
}
