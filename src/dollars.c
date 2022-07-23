/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:51:32 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/22 19:09:46 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	new = NULL;
	if (ft_strchr(command, '$') && ft_strlen(command) != 1)
	{
		pos = get_dollar_pos(command);
		var = ft_substr(command, pos + 1, ft_strlen(command) - pos + 1);
		if (get_elem(data->h_env, var) || get_elem(data->h_var, var))
			value = get_var(data, var);
		else
		{
			free(var);
			return (NULL);
		}
		free(var);
		new = dollar_substitute(command, value, pos);
		free(value);
		return (new);
	}
	else if (ft_strchr(command, '$') && ft_strlen(command) == 1)
		return (ft_straddc(new, '$'));
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
	str = ft_substr(command, 0, pos);
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
