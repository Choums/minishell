/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:39:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/02 14:56:54 by chaidel          ###   ########.fr       */
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

typedef struct s_redirection
{
	char	**in;
	int		token_in;
	char	**out;
	int		token_out;
}	t_redirection;

typedef struct s_command
{
	char			*all_pipe;
	char			**tab_cmd;
	char			**tab_token;
	t_redirection	*tab_redirection;

}	t_command;



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
void	cat_var(t_data *data, char *var);
void	add_var(t_data *data, char *var);
size_t	name_len(char *var);
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
void	mother_board(t_data *data, t_command *cmd);
void	process(t_data *data, t_command *cmd);
void	display_here(void);
char	*get_lim(char **args);
void	redir(t_redirection *tab);
void	out_redir(char *file);
void	in_redir(char *file);
void	append_mode(char *file);
void	heredoc(t_data *data, char **args);

/*	List */
void	set_var(t_data *data, char *content);
void	supp_elem(t_list **head, char *var);
void	supp_fst_elem(t_list **head, t_list *tmp);
void	update_elem(t_data *data, char *var);
char	*get_elem(t_list **head, char *var);
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

/*
AFFICHAGE_C----------------------------------------------------------------------
*/
void	ft_affiche_t_command(t_command	*(*table_pipe));

/*
COMMAND_C------------------------------------------------------------------------
*/
char	*ft_cup_all_cmd(char *tmp, char *tmp_cmd);
void	copy_cmd(t_command *(*table_pipe), int	nb_pp, char *cmd);
t_command	**ft_parse_cmd(t_command *(*table_pipe), int number_pipe);
/*
REDIRECTION_C--------------------------------------------------------------------
*/
int			ft_count_redirection(char *str, char c_redirect);
t_command	**ft_redirection_init(t_command	*(*table_pipe), int number_pipe);
void		ft_parse_redir_in(t_command *(*table_pp), int nb_pp, char c);
void		ft_parse_redir_out(t_command *(*table_pp), int nb_pp, char c);

/*
PARSING_C------------------------------------------------------------------------
*/
int			ft_count_pipe(char *line);
t_command	**ft_parse_pipe(t_command *(*table_pipe), char *line);
void		ft_free_doutab(char **tab);
int			ft_doubletab_len(char **tab);
void		ft_parsing(t_data *data, char *line);

#endif
