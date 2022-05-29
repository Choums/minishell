/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:39:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/29 17:59:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEFAULT_PATH_VALUE "PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/chardefs.h>
# include "../libft/libft.h"
# include "get_next_line.h"

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
void	print_vars(t_list **head); // DEBUG, à supp.
int		is_exit(t_data *data, char *line);
void	echo(char *arg);
void	pwd(void);
void	unset(t_data *data, char *var);
void	export(t_data *data, char *var);
int		check_var(char *var);
void	add_var(t_data *data, char *var);
void	display_env(t_data *data);
void	sort_env(char **env);
void	print_export(char **env);
void	pwd(void);
void	check_dir(t_data *data, char *path);
void	check_path(t_data *data, char *path);
void	change_dir(t_list **h_env, char *path);
void	goto_home(t_list **h_env);
int		is_oldpwd(t_list **h_env);
void	create_oldpwd(t_list **h_env);
void	goto_oldpwd(t_list **h_env);


/*	Exec */
char	*find_bin(t_list *lst_path, char *bin);
void	process(t_data *data, char *command, char **args, char **envp);
void	heredoc(t_data *data, char **args);
void	display_here(void);
char	*get_lim(char **args);

/*	List */
void	set_var(t_data *data, char *content);
void	supp_elem(t_list **head, char *var);
void	supp_fst_elem(t_list **head, t_list *tmp);
void	update_elem(t_list **head, char *var, char *content);
char	*get_elem(t_list **head, char *content);
char	*get_var(t_data *data, char *var);
char	*which_dollar(t_data *data, char *command);
size_t	get_dollar_pos(char *str);
char	*dollar_substitute(char *command, char *value, size_t pos);
char	**lst_dup(t_list **head);
size_t	get_lst_len(t_list **head);

/*	Utils */
void	free_double_tab(char **tab);
void	print_double_tab(char **tab); //DEBUG


/*	Errors */
void	ft_err(char *err);
void	export_err(char *command, int alloc);


// struct sigaction {
//     void     (*sa_handler) (int);
//     void     (*sa_sigaction) (int, siginfo_t *, void *);
//     sigset_t   sa_mask;
//     int        sa_flags;
//     void     (*sa_restorer) (void);
// };

#endif
