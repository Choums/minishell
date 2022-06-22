/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:17:19 by root              #+#    #+#             */
/*   Updated: 2022/06/22 18:20:53 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
 *	Ajoute une var à la lst.
 *	La lst. sera init. si ce n'est pas déjà le cas
*/
void	set_var(t_data *data, char *content)
{
	if (&(*data->var) == NULL)
	{
		data->var = ft_lstnew(content);
		data->h_var = &data->var;
	}
	else
		if (get_elem(data->h_var, content) == NULL)
			ft_lstadd_back(&data->var, ft_lstnew(content));
}

/*
 *	Retire le maillon de la chaine
*/
void	supp_elem(t_list **head, char *var)
{
	t_list	*tmp;
	t_list	*lst;

	tmp = (*head);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var)) == 0)
		{
			if (tmp->previous == NULL)
			{
				supp_fst_elem(head, tmp);
				return ;
			}
			else if (tmp->previous && tmp->next)
			{
				tmp->previous->next = tmp->next;
				tmp->next->previous = tmp->previous;
				ft_lstdelone(tmp, del);
				return ;
			}
			else if (tmp->next == NULL)
			{
				lst = tmp;
				tmp->previous->next = NULL;
				ft_lstdelone(lst, del);
				return ;
			}
		}
		else
			tmp = tmp->next;
	}
}

void	supp_fst_elem(t_list **head, t_list *tmp)
{
	if (*head == NULL)
		return ;
	if ((*head)->next == NULL)
	{
		ft_lstdelone(tmp, del);
		(*head) = NULL;
	}
	else
	{
		(*head) = tmp->next;
		ft_lstdelone(tmp, del);
		(*head)->previous = NULL;
	}
}

/*
 *	Update la var donnée
*/
void	update_elem(t_data *data, char *var)
{
	t_list	*tmp;
	size_t	len;

	len = 0;
	while (var[len] != '=' && var[len])
		len++;
	tmp = (*data->h_env);
	while (tmp)
	{
			// printf("up env\n");
		if (ft_strncmp(tmp->content, var, len - 1) == 0)
		{
			del(tmp->content);
			tmp->content = ft_strdup(var);
			break ;
		}
		else
			tmp	= tmp->next;
	}
	tmp = (*data->h_var);
	while (tmp)
	{
		// printf("up var\n");
		if (ft_strncmp(tmp->content, var, len - 1) == 0)
		{
			del(tmp->content);
			tmp->content = ft_strdup(var);
			break ;
		}
		else
			tmp	= tmp->next;
	}
}

/*
 *	Cherche un element dans la list donnée et le renvoie
 *	NULL si l'elem n'existe pas
*/
char	*get_elem(t_list **head, char *var)
{
	t_list	*tmp;
	size_t	len;

	len = name_len(var);
	tmp = (*head);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, len) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 *	Cherche la var dans l'env et la lst des var et renvoie sa valeur
 *	La value est a free apres son usage
*/
char	*get_var(t_data *data, char *var)
{
	t_list	*tmp;
	char	*value;

	tmp = (*data->h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var) - 1) == 0)
		{
			value = ft_substr(tmp->content, ft_strlen(var) + 1, ft_strlen(tmp->content) - ft_strlen(var));
			return (value);
		}
		else
			tmp = tmp->next;
	}
	tmp = (*data->h_var);
	while (tmp)
	{
		// printf("var: %s\nln: %zu+1\nret: %d\n", tmp->content, ft_strlen(var) - 1, ft_strncmp(tmp->content, var, ft_strlen(var)-1));
		if (ft_strncmp(tmp->content, var, ft_strlen(var) - 1) == 0)
		{
			value = ft_substr(tmp->content, ft_strlen(var) + 1, ft_strlen(tmp->content) - ft_strlen(var));
			return (value);
		}
		else
			tmp = tmp->next;
	}
	return (NULL);
}

/*
 *	Vérifie si la string possede un $
 *	Vérifie ensuite si la valeur recheché est '?' ou le nom d'une var
 *	Échange le nom de la var par sa valeur dans la string
 *	Si aucun des deux, une valeur NULL est renvoyé
 *	VAR=value
 *	$VAR
*/
char	*which_dollar(t_data *data, char *command)
{
	char	*var;
	char	*value;
	size_t	pos;
	char	*new;

	if (ft_strchr(command, '$') && ft_strlen(command) != 1)
	{
		pos = get_dollar_pos(command);
		if (command[pos + 1] == '?')
			return (0); //Signaux a faire
		var = ft_substr(command, pos + 1, ft_strlen(command) - pos + 1);
		printf("var: %s\n", var);
		if (get_elem(data->h_env, var) || get_elem(data->h_var, var))
			value = get_var(data, var);
		else
		{
			free(var);
			return (NULL);
		}
		printf("get_var: %s\n", value);
		free(var);
		new = dollar_substitute(command, value, pos);
		free(value);
		printf("new: %s\n", new);
		return (new);
	}
	return (NULL);
}


/*
 *	Substitue $var par sa valeur
*/
char	*dollar_substitute(char *command, char *value, size_t pos)
{
	char	*str;
	char	*join;

	if (pos == 0)
		return (ft_strdup(value));
	str = ft_substr(command, 0, ft_strlen(command) - pos + 2);
	join = ft_join(str, value);
	return (join);
}

/*
 *	Retourne la position du '$' dans la string
*/
size_t	get_dollar_pos(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}



/*
 *	DEBUG
 *	PRINT LA LST DONNEES
*/
void	print_vars(t_list **head)
{
	t_list	*tmp;

	tmp = (*head);
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
