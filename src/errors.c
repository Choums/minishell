/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 21:35:36 by root              #+#    #+#             */
/*   Updated: 2022/06/22 13:35:12 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_err(char *command, int alloc)
{
	// printf("check non valid\n");
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putendl_fd("': not a valid identfier", STDERR_FILENO);
	if (alloc)
		free(command);
}