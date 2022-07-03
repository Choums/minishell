/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:47:01 by root              #+#    #+#             */
/*   Updated: 2022/07/03 15:30:34 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exiter(t_data *data, t_command **tab, char **args)
{
	int			i;
	long long	code;

	if (!args[1])
		is_exit(data, tab);
	check_exit_args(args);
	i = ft_doubletab_len(args);
	if (i > 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		// status = 127;
	}
	else
	{
		code = atoi_exit(args[1]);
		// status = code % 256;
	}
	is_exit(data, tab);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == -1 || c == 32)
		return (1);
	return (0);
}

long long	atoi_exit(char *str)
{
	int				sign;
	long long		nbr;
	int				j;

	nbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + ((long long)*str - 48);
		str++;
		j++;
	}
	// j >= 20 error numeric argument required
	return (nbr * sign);
}

void	check_exit_args(char *arg)
{
	int	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isspace(arg[i]))
			if (!ft_isdigit(arg[i]))
				msg_err("exit", "numeric argument required", 2);
		i++;
	}
}

int	is_exit(t_data *data, t_command **tab)
{

	rl_clear_history();
	ft_lstclear(&data->env, del);
	ft_lstclear(&data->var, del);
	ft_lstclear(&data->path, del);
	// free_struc(tab);
	exit(EXIT_SUCCESS);
}
