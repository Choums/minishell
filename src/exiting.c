/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:47:01 by root              #+#    #+#             */
/*   Updated: 2022/07/22 20:04:31 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Verfie les arguments et definie la facon d'exit
 *	-------------------------------------
 *	errors
 * 	too many arguments | status 1 | no quit
 *	args digit supp a 2
 *	1er args digit si supp a 2
 *	-----
 *	numeric arguments required | status 2 | quit
 *	args non digit (un + ou un - sont autorisé)
 *	args supp a 2 dont le 1er est non digit
 *	-------------------------------------
*/
void	exiter(t_data *data, t_command **tab, char **args)
{
	int			i;
	long long	code;
	int			n_char;

	n_char = 0;
	if (!args[1])
		is_exit(data, tab, 0);
	if (!check_exit_args(args[1]))
		exit_err(data, tab, args[1]);
	i = ft_doubletab_len(args);
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit", STDERR_FILENO);
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		g_signal.status = 1;
		return ;
	}
	else
	{
		code = atoi_exit(args[1], &n_char);
		if (n_char == 1)
			exit_err(data, tab, args[1]);
		g_signal.status = code % 256;
	}
	is_exit(data, tab, code);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == -1 || c == 32)
		return (1);
	return (0);
}

long long	atoi_exit(char *str, int *n_char)
{
	int				sign;
	long long		nbr;
	int				j;

	nbr = 0;
	sign = 1;
	j = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
		j++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + ((long long)*str - 48);
		str++;
		j++;
	}
	if ((j >= 20 && sign > 0) || (j >= 21 && sign < 0))
		*n_char = 1;
	return (nbr * sign);
}

int	check_exit_args(char *arg)
{
	int	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	if (ft_atoi_unsigned_long_long(arg)
		== (unsigned long long)-1 && ft_strlen(arg) > 1)
		return (0);
	if (ft_atoi_unsigned_long_long(arg)
		== (unsigned long long)0 && ft_strlen(arg) > 1)
		return (0);
	return (1);
}

int	is_exit(t_data *data, t_command **tab, int status)
{
	rl_clear_history();
	ft_lstclear(&data->env, del);
	ft_lstclear(&data->var, del);
	ft_lstclear(&data->path, del);
	free_struc(tab);
	exit(status);
}
