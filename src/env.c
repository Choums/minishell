/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:40:50 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/24 22:12:53 by root             ###   ########.fr       */
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
	data->env = ft_lstnew(env[n++]);
	// printf("\n%s\nvar: %s", data->env->content, env[i - 1]);
	while (n < i)
		ft_lstadd_back(&data->env, ft_lstnew(env[n++]));
	// data->env = (char **)malloc(sizeof(char *) * i);
	// if (!data->env)
	// 	return ;
	// while (n < i)
	// {
	// 	data->env[n] = env[n];
	// 	n++;
	// }
}


/*
 *	export [var]
 *	export -> ajoute la var a env 
 *	
*/
// void	export(t_data *data, char *var)
// {
	
// }

/*
 *	unset [var]
 *	Retire la var de l'env 
 *	Supp. le maillon de la var
 *	tmp->previous->next = tmp->next
 *	tmp->next->previous = tmp->previous
*/
void	unset(t_data *data, char *var)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, var, ft_strlen(var)))
		{
			tmp->previous->next = tmp->next;
			tmp->next->previous = tmp->previous;	
			// free(tmp);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}

void	print_env(const t_data data)
{
	t_list	*tmp;

	tmp = data.env;
	while (tmp)
	{
		ft_putendl_fd(tmp->content, STDOUT_FILENO);
		tmp = tmp->next;
	}
}
