/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:40:50 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/25 20:57:24 by root             ###   ########.fr       */
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
	data->h_env = &data->env;
}


/*
 *	export [var]
 *	export -> ajoute la var a env 
 *	
*/
void	export(t_data *data, char *var)
{
	t_list	*tmp;
	
	tmp = data->var;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, var, ft_strlen(var)))
		{
			ft_lstadd_back(&data->env, ft_lstnew(tmp->content));
			return ;
		}
		else
			tmp = tmp->next;
	}
}

/*
 *	unset [var]
 *	Retire la var de l'env 
 *	Supp. le maillon de la var
 *	tmp->previous->next = tmp->next
 *	tmp->next->previous = tmp->previous
 *	Cas a gerer => Premier	| previous NULL
 *				=> Milieu	| previous et next true
 *				=> Fin		| next NULL
*/
void	unset(t_data *data, char *var)
{
	t_list	*tmp;
	t_list	*lst;
	
	tmp = (*data->h_env);
	while (tmp)
	{
		if (ft_strnstr(tmp->content, var, ft_strlen(var)))
		{
			if (tmp->previous == NULL)
			{
				(*data->h_env) = tmp->next;
				free(tmp);
				(*data->h_env)->previous = NULL;
				return ;
			}
			else if (tmp->previous && tmp->next)
			{
				tmp->previous->next = tmp->next;
				tmp->next->previous = tmp->previous;	
				free(tmp);
				return ;	
			}
			else if (tmp->next == NULL)
			{
				free(tmp);
				lst = ft_lstlast((*data->h_env));
				printf("last: %s\n", lst->content);
				lst->next = NULL;
				return ;
			}
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
