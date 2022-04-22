/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:40:50 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/22 15:30:12 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Env
 *	Recup toutes les variables d'environement
 *	env et export sont des builtins a faire
*/
void	get_env(t_data *data, char **env)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (env[i])
		i++;	
	data->env = (char **)malloc(sizeof(char *) * i);
	if (!data->env)
		return ;
	while (n < i)
	{
		data->env[n] = env[n];
		n++;
	}
}


/*
 *	export [var]
 *	export -> ajoute la var a env 
 *	
*/
// void	export(t_data *data)
// {
	
// }

// /*
//  *	unset [var]
//  *	Retire la var de l'env 
// */
// void	unset(t_data *data)
// {
	
// }

void	print_env(const t_data data)
{
	int	i;

	i = 0;
	while (data.env[i])
	{
		ft_putendl_fd(data.env[i], STDOUT_FILENO);
		i++;
	}
}
