/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:39:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/21 17:26:12 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEF "PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/chardefs.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <signal.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
	int		in_fd;
	int		out_fd;
	int		cpy_in;
	int		cpy_out;
	char	**in;
	char	**token_in;
	char	**out;
	char	**token_out;
}	t_redirection;

typedef struct s_command
{
	char			*all_pipe;
	char			**tab_cmd;
	char			**tab_token;
	t_redirection	*tab_redir;
	int				len_pipe;

}	t_command;

typedef struct s_signal
{
	int	quit;
	int	sigint;
	int	pid;
	int	exit_status;
}	t_signal;

extern t_signal	g_signal;

/*	Builtin */
void	get_env(t_data *data, char **envp);
void	set_env(t_data *data);
void	get_path(t_data *data);
void	set_path(t_data *data, char **path);
void	print_env(t_list **h_env);
void	print_vars(t_list **head); // DEBUG, à supp.
int		is_exit(t_data *data, char *line);
void	echo(char **arg);
int		check_atr_n(char **args);
void	pwd(void);
void	unset(t_data *data, char **var);
void	export(t_data *data, char **var);
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
void	change_dir(t_list **h_env, char **path);
void	goto_home(t_list **h_env);
int		is_oldpwd(t_list **h_env);
void	create_oldpwd(t_list **h_env);
void	goto_oldpwd(t_list **h_env);

/*	Exec */
char	*find_bin(t_list *lst_path, char *bin);
void	mother_board(t_data *data, t_command **cmd);
int		is_builtin(t_command *cmd);
void	exec_builtin(t_command *cmd, t_data *data);
void	run_builtin(t_data *data, t_command *cmd);
void	process(t_data *data, t_command *cmd, int *pipefd, int pos);
void	redir_pipe(int *pipefd, int pos, int n_pipe);
void	display_here(void);
char	*get_lim(t_redirection *args);
void	redir(t_data *data, t_redirection *tab);
void	redirect(t_redirection *tab);
void	restore_redir(t_redirection *tab);
void	out_redir(t_data *data, t_redirection *tab, char *file);
void	in_redir(t_data *data, t_redirection *tab, char *file);
void	append_mode(t_data *data, t_redirection *tab, char *file);
void	heredoc(t_data *data, t_redirection *args);
int		opening_mode(char *pathname);
void	pipex(t_data *data, t_command **cmd);
int		*create_pipes(int num);
void	close_pipes(int *pipefd, int n_pipe);
void	close_unused_pipes(int *pipefd, int pos, int n_pipe);

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
size_t	get_cmd_num(t_command **cmd);
void	pipe_err(int *pipefd, int i);

/*	Errors */
void	ft_err(char *err);
void	export_err(char *command, int alloc);

/*
AFFICHAGE_C----------------------------------------------------------------------
*/
void	ft_affiche_t_command(t_command	*(*table_pipe));

/*
COMMAND_C------------------------------------------------------------------------
*/
char	*ft_cup_all_cmd(char *tmp, char *tmp_cmd, char c);
void	copy_cmd(t_command *(*table_pipe), int	nb_pp, char *cmd);
t_command	**ft_parse_cmd(t_command *(*table_pipe), int number_pipe);
/*
REDIRECTION_C--------------------------------------------------------------------
*/
int		ft_count_redirection(char *str, char c_redirect);
t_command	**ft_redirection_init(t_command	*(*table_pipe), int number_pipe);
void	ft_parse_redir_in(t_command *(*table_pp), int nb_pp, char c);
void	ft_parse_redir_out(t_command *(*table_pp), int nb_pp, char c);
char	*ft_search_redir(char *str, char c);

/*
PARSING_C------------------------------------------------------------------------
*/
int		ft_count_pipe(char *line);
t_command	**ft_parse_pipe(t_command *(*table_pipe), char *line);
int		ft_doubletab_len(char **tab);
t_command	**ft_parsing(t_data *data, char *line, t_command *(*table_pipe));
/*
TOKENIZER_C----------------------------------------------------------------------
*/
int		check_builtin(char *str);
int		struc_len(t_command **table_pipe);
void	tokenizer_cmd(t_command **table_pipe, int nb_pp, t_data *data);
void	tokenizer_redir_in(t_command **table_pipe, int np);
void	tokenizer_redir_out(t_command **table_pipe, int np);

/*
FREE-----------------------------------------------------------------------------
*/
void	ft_free_doutab(char **tab);
void	free_struc(t_command **table_pipe);

/*
SIGNAL_C-------------------------------------------------------------------------
*/
void	ft_signal(int sig, siginfo_t *info, void *context);
void	sig_int(int sig, siginfo_t *info, void *context);
void	sig_quit(int sig, siginfo_t *info, void *context);
void	signal_init(void);

/*
SPLIT_PIPE_C---------------------------------------------------------------------
*/
char	**split_pipe(char *str);

/*
VERIF_LINE_C---------------------------------------------------------------------
*/
int		verif_quote(char *line);
int		verif_line(char *line);

#endif
