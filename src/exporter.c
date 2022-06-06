/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:14:47 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/06 19:44:51 by root             ###   ########.fr       */
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
 *	argument var a mettre en double tab et boucler dessus pour chaque arg.
 *	--------------------------------
 *	Seul le 1er '=' signifie la valeur, les autres ne comptent pas.
 *	Une var sans value peut etre export mais elle n'apparait pas (via env).
 *	export sans arg affiche les vars sans value.
 *	L'expansion des var.
 *	La var '_' n'est pas affiché en export sans arg.
 *	Une var sans value déjà export ne peut plus l'être.
 *	Export une var déjà export avec une value différente mettra à jour sa value.
 *	La var doit commencer par une lettre (ou un '_').
 *	La var doit avoir que des alphanum dans son nom (hormis '_').
 *	Le '+' n'est tolerer qu'avant le =.
 *	"+=" concatene la précedente value avec la nouvelle.
*/
void	export(t_data *data, char **var)
{
	int		alloc;
	size_t	i;

	i = 1;
	alloc = 0;
	// printf("%s\n", var);
	while (var[i])
	{
		if (var == NULL)
		{
			display_env(data);
			return ;
		}
		if (ft_strchr(var, '$'))
		{
			var = which_dollar(data, var);
			alloc = 1;
		}
		if (check_var(var))
		{
			if (var[name_len(var)] == '=' && var[name_len(var) - 1] == '+')
				cat_var(data, var);
			else
				add_var(data, var);
		}
		else
			export_err(var, alloc);
		if (alloc)
			free(var);		
		i++;
	}
}

int	check_var(char *var)
{
	size_t	i;
	int		first_alpha;

	first_alpha = 0;
	i = 0;
	if (!var || !var[i])
		return (0);
	else if (ft_isalpha(var[i]) || var[i] == '_')
		first_alpha = 1;
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '+' && var[i + 1] == '=')
			return (1);
		if (!first_alpha || !ft_isalnum(var[i]) || !(var[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

/*
 *	Concatene la valeur donnée avec la valeur précédente
 *	name+=value_to_add
 *	recup la var via son nom
 *	ajoute la value a la precedente
 *	-------------------------------------
 *	taille var et len sont egaux	-> Pas de value => si la var n'existe pas
 														elle est init avec value NULL
														 (diff d'une var sans value)
 *	export test+=	=>	test=
 *	export ss		=>	ss
 *	-------------------------------------
 *	test=salut
 *	export test+=_hola	=>	test=salut_hola
 *	la value donné se concatene a la precedente
*/
void	cat_var(t_data *data, char *var)
{
	t_list	*tmp;
	size_t	len;

	len = name_len(var);
	printf("%c\n", var[len]);
	if (var[len] == '=' && ft_strlen(var) - 1 == len)
	{
		printf("in\n");
		add_var(data, NULL);
	}
	else if (ft_strlen(var) - 1 > len)
	{
		
	}
}

/*
 *	Ajoute une var a l'env
 *	----------------------
 *	Si la var existe dans l'env et elle a une value	=>	La value de la var est mise a jour. (dans la lst des var aussi)
 *	Si la var existe dans l'env mais n'a pas de value	=>	La value est ajouté la var.
 *	Si la var n'est pas dans l'env => La var est ajouté a l'env. (avec ou sans value)
 *	----------------------
 *	Recup le nom de la var
 *	Check si elle existe :	mise a jour
 *	si elle n'existe pas :	add
*/
void	add_var(t_data *data, char *var)
{
	t_list	*tmp;
	size_t	len;

	len = name_len(var);
	// printf("%s | %p\n", var, get_elem(data->h_env, var));
	if (var[len] == '=' && (get_elem(data->h_env, var) || get_elem(data->h_var, var))) //mod
	{
		// printf("in up\n");
		if (get_elem(data->h_env, var) == NULL)
			ft_lstadd_back(&data->env, ft_lstnew(var));
		update_elem(data, var);
	}
	else if (get_elem(data->h_env, var) == NULL && get_elem(data->h_var, var)) //add existing
	{
		tmp = (*data->h_var);
		while (tmp)
		{
			if (ft_strncmp(tmp->content, var, ft_strlen(var)) == 0)
			{
				// printf("ex var %s\n", var);
				ft_lstadd_back(&data->env, ft_lstnew(tmp->content));
				return ;
			}
			else
				tmp = tmp->next;
		}	
	}
	else // non existing var (declaration)
	{
		// printf("add\n");
		ft_lstadd_back(&data->env, ft_lstnew(var));
		ft_lstadd_back(&data->var, ft_lstnew(var));
	}
}

/*
 *	Renvoi la taille du nom de la var
 *	len est soit:	l'index du '='
 *					la fin du nom
*/
size_t	name_len(char *var)
{
	size_t	len;

	len = 0;
	while (var[len] != '=' && var[len])
		len++;
	return (len);
}

/*	When no arguments are given, the results  are  unspecified.
 *	Affiche les var dans l'ordre ASCII
 *	La valeur des var est encadrée par des " "
 *	Affiche les var sans value
 *	-------------------------
*/
void	display_env(t_data *data)
{
	char	**env;

	env = lst_dup(data->h_env);
	sort_env(env);
	print_export(env);
	free_double_tab(env);
}

void	sort_env(char **env)
{
	char 	*swap;
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				swap = env[i];
				env[i] = env[j];
				env[j] = swap;
			}
			j++;
		}
		i++;
	}
}

void	print_export(char **env)
{
	size_t	i;
	size_t	j;
	size_t	egal;
	i = 0;
	while (env[i])
	{
		j = 0;
		egal = 1;
		ft_putstr_fd("declare -x ", STDIN_FILENO);
		while (env[i][j])
		{
			ft_putchar_fd(env[i][j], STDIN_FILENO);
			if (env[i][j] == '=' && egal--)
				ft_putchar_fd('"', STDIN_FILENO);
			j++;
		}
		if (!egal)
			ft_putchar_fd('"', STDIN_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		i++;
	}
}

/*
 *	Dupplique la lst donnée et retourne un double tab.
 *	1- Prendre la taille de la lst.
 *	2- Init le tab.
 *	3- Boucle sur la taille, dupplique chaque maillon.
*/
char	**lst_dup(t_list **head)
{
	size_t	len;
	size_t	i;
	char	**dup;
	t_list	*tmp;

	i = 0;
	tmp = (*head);
	len = get_lst_len(head) - 1;
	dup = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		if (ft_strncmp(tmp->content, "_=", ft_strlen("_=")))
			dup[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	dup[len] = NULL;
	return (dup);
}

size_t	get_lst_len(t_list **head)
{
	t_list	*tmp;
	size_t	len;

	tmp = (*head);
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}