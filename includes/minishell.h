/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:39:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/02 10:53:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEFAULT_PATH_VALUE "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"

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


/*	Builtin */
void	get_env(t_data *data, char **envp);
void	set_env(t_data *data);
void	get_path(t_data *data);
void	set_path(t_data *data, char **path);
void	print_env(t_list **h_env);
void	print_var(t_list **head); // A supp.
int		is_exit(t_data *data, char *line);
void	echo(char *arg);
void	pwd(void);
void	unset(t_data *data, char *var);
void	export(t_data *data, char *var);
void	pwd(void);
void	check_dir(t_data *data, char *path);
void	change_dir(t_list **h_env, char *path);
void	goto_home(t_list **h_env);
int		is_oldpwd(t_list **h_env);
void	create_oldpwd(t_list **h_env);
void	goto_oldpwd(t_list **h_env);


/*	List */
void	set_var(t_data *data, char *content);
void	supp_elem(t_list **head, char *var);
void	supp_fst_elem(t_list **head, t_list *tmp);
void	update_elem(t_list **head, char *var, char *content);

/*	Utils */
void	free_double_tab(char **tab);


#endif
