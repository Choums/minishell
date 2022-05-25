/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:14:47 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/25 19:06:49 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	The  shell shall give the export attribute to the variables
 *	corresponding to the specified  names,  which  shall  cause
 *	them to be in the environment of subsequently executed com‐
 *	mands. If the name of a variable is followed by =word, then
 *	the value of that variable shall be set to word.
 *	
*/


/*
 *	export [var]
 *	export -> ajoute la var a l'env.
 *	La var est mise en fin de chaine
*/
void	export(t_data *data, char *var)
{
	t_list	*tmp;
	int		alloc;
	
	// printf("%s\n", var);
	if (var == NULL)
	{
		display_env(data);
		return ;
	}
	if (ft_strchr(var, '$'))
		var = which_dollar(data, var);
	tmp = data->var;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var)) == 0)
		{
			ft_lstadd_back(&data->env, ft_lstnew(tmp->content));
			return ;
		}
		else
			tmp = tmp->next;
	}
	if (alloc)
		free(var);
}



/*	When no arguments are given, the results  are  unspecified.
 *	Affiche les var dans l'ordre ASCII
 *	La valeur des var est encadrée par des " "
 *	-------------------------
 *	1-	Duppliquer la list env
 *	2-	
*/
void	display_env(t_data *data)
{
	t_list	*tmp;

	tmp = sorted_list(data->h_env);
	while (tmp)
	{
		ft_putendl_fd(tmp->content, STDOUT_FILENO);
		tmp = tmp->next;
	}
}

/*
 *	Dupplique la list puis la tri dans l'ordre ASCII
*/
t_list	*sorted_list(t_list **head)
{
	
}