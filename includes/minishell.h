/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:39:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/25 17:35:57 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/chardefs.h>
# include "../libft/libft.h"

typedef struct s_data
{
	t_list	*env;
}	t_data;

typedef struct s_command
{
	int		nb_cmd;
	char	**tab_cmd;
	char	**tab_pipe;
}	t_command;

/*
ENV_C----------------------------------------------------------------------------
*/
void	get_env(t_data *data, char **envp);
void	print_env(const t_data data);
int		is_exit(t_data *data, char *line);
void	echo(char *arg);
void	unset(t_data *data, char *var);
/*
PARSING_C------------------------------------------------------------------------
*/
int		ft_affiche_struc(t_command *(*tab_cmd));
void	ft_free_doutab(char **tab);
int		ft_doubletab_len(char **tab);
t_command		**ft_parsing(char *line);

#endif
