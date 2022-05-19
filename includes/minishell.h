/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:39:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/19 16:24:57 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEFAULT_PATH_VALUE "PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"

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
	t_list	**h_env;
	t_list	*var;
	t_list	**h_var;
	t_list	*path;
}	t_data;

typedef struct s_command
{
	int		nb_cmd;
	char	**redirection;
	char	**tab_cmd;
	char	**tab_pipe;
}	t_command;

/*
ENV_C----------------------------------------------------------------------------
*/
void	get_env(t_data *data, char **envp);
void	set_env(t_data *data);
void	get_path(t_data *data);
void	set_path(t_data *data, char **path);
void	print_env(t_list **h_env);
void	print_vars(t_list **head); // A supp.
char	*get_var(t_data *data, char *var);
int		is_exit(t_data *data, char *line);
void	echo(char *arg);
void	pwd(void);
void	unset(t_data *data, char *var);
/*
PARSING_C------------------------------------------------------------------------
*/
int		ft_affiche_struc(t_command *(*tab_cmd));
void	ft_free_doutab(char **tab);
int		ft_doubletab_len(char **tab);
void	ft_parsing(char *line);

#endif
