/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:39:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/25 23:21:54 by chaidel          ###   ########.fr       */
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
# include <readline/history.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include <errno.h>

// int WEXITSTATUS(int status);

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define LIMIT 9223372036854775808

typedef struct s_data
{
	t_list	*env;
	t_list	**h_env;
	t_list	*var;
	t_list	**h_var;
	t_list	*path;
	int		*pipefd;
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
	char	**tab_fusion;
	char	**tab_fusion_to;
}	t_redirection;

typedef struct s_command
{
	char			*all_pipe;
	char			**tab_cmd;
	char			**tab_token;
	t_redirection	*tab_redir;
	int				len_pipe;
	char			*redir_place;

}	t_command;

typedef struct s_signal
{
	int	quit;
	int	sigint;
	int	pid;
	int	nt_status;
	int	status;
}	t_signal;

extern t_signal	g_signal;

/*	Builtin */
void		get_env(t_data *data, char **envp);
void		set_env(t_data *data);
void		get_path(t_data *data);
void		set_def_path(t_data *data);
void		set_path(t_data *data, char **path);
int			print_env(t_list **h_env);
int			echo(char **arg);
int			no_arg(void);
int			display_n(char **args, size_t i, size_t j);
int			check_atr_n(char **args);
int			pwd(void);
int			unset(t_data *data, char **var);
int			is_valid_id(char *var);
int			export(t_data *data, char **var);
int			check_var(char *var);
void		check_existing(t_data *data, char *var, size_t len);
void		cat_var(t_data *data, char *var);
void		add_var(t_data *data, char *var);
size_t		name_len(char *var);
int			display_env(t_data *data);
void		sort_env(char **env);
void		print_export(char **env);
int			check_dir(t_data *data, char **args);
int			change_err(char *pathname, int alloc);
int			change_dir(t_data *data, char *path, int alloc);
void		update_pwd(t_data *data);
int			goto_home(t_data *data);
int			goto_homepath(t_data *data, char *path);
int			goto_oldpwd(t_data *data);
int			is_oldpwd(t_list **h_env);
void		create_oldpwd(t_data *data);
void		check_prim(t_data *data);
void		inception(t_data *data);
int			is_exit(t_data *data, t_command **tab, int status);
void		exiter(t_data *data, t_command **tab, char **args);
int			ft_isspace(int c);
long long	atoi_exit(char *str, int *n_char);
int			check_exit_args(char *arg);

/*	Exec */
char		*find_bin(t_data *data, char *bin);
int			check_cmd(char *cmd);
int			check_cmd_neg(char *cmd, struct stat path_stat);
void		mother_board(t_data *data, t_command **cmd);
void		one_exit(t_data *data, t_command **cmd);
int			is_builtin(t_command *cmd);
void		exec_builtin(t_command *cmd, t_data *data);
void		run_builtin(t_data *data, t_command *cmd);
int			process(t_data *data, t_command *cmd, int pos);
void		kill_kid(t_data *data, char **env);
void		redir_pipe(int *pipefd, int pos, int n_pipe);
void		proc_redir(t_data *data, t_command *cmd);
void		display_here(void);
char		*get_lim(t_redirection *args);
int			redir(t_data *data, t_redirection *tab);
int			redir_sc(t_redirection *tab, int i);
void		restore_redir(t_redirection *tab);
int			close_cpy(t_redirection *tab);
int			out_redir(t_redirection *tab, char *file);
int			in_redir(t_redirection *tab, char *file);
int			append_mode(t_redirection *tab, char *file);
int			heredoc(t_data *data, t_redirection *tab, char *lim);
int			here_linker(t_redirection *tab, int file, char *new_line);
int			end_sig(char *line, char *lim, char *end, int count);
char		*check_expand(t_data *data, char *line);
int			opening_mode(char *pathname);
int			pipex(t_data *data, t_command **cmd);
void		end_pipes(t_data *data, t_command **cmd, pid_t child);
int			*create_pipes(int num);
void		close_pipes(int *pipefd, int n_pipe);
int			check_perm(char *path);
char		*get_cmd(t_data *data, char *cmd);

/*	List */
void		set_var(t_data *data, char *content);
void		supp_elem(t_list **head, char *var);
void		supp_fst_elem(t_list **head, t_list *tmp);
void		update_elem(t_data *data, char *var);
void		update_elem_vars(t_data *data, char *var, size_t len);
char		*get_elem(t_list **head, char *var);
char		*get_var(t_data *data, char *var);
char		*get_hvar(t_data *data, char *var);
char		*which_dollar(t_data *data, char *command);
size_t		get_dollar_pos(char *str);
char		*dollar_substitute(char *command, char *value, size_t pos);
char		**lst_dup(t_list **head);
size_t		get_lst_len(t_list **head);

/*	Utils */
void		free_double_tab(char **tab);
void		print_double_tab(char **tab); //DEBUG
size_t		get_cmd_num(t_command **cmd);
void		data_init(t_data *data);

/*	Errors */
int			pipe_err(int *pipefd, int i);
void		export_err(char *command);
void		exit_err(t_data *data, t_command **tab, char *arg);
int			msg_err(char *cmd, char *msg, int status);
int			redir_err(char *file);
/*
AFFICHAGE_C----------------------------------------------------------------------
*/
void		ft_affiche_t_command(t_command	*(*table_pipe));
/*
EXPAND_C-------------------------------------------------------------------------
*/
char		*put_dollar(t_data *data, char *expand, char *str, int *i);
char		*sexp(t_data *data, char *str);

/*
EXPAND_UTILS_C-------------------------------------------------------------------
*/
int			count_var(char *str);
int			linear_check_tab(char **tab, int len_tab);
/*
COMMAND_C------------------------------------------------------------------------
*/
char		*ft_cup_all_cmd(char *tmp, char *tmp_cmd, char c, int i);
void		count_cmd(t_command	*(*table_pipe), int nb_pp, char *cut_cmd);
void		copy_cmd(t_command *(*table_pipe), int nb_pp, char *cmd);
t_command	**ft_parse_cmd(t_command *(*table_pipe), int number_pipe);
/*
COMMAND_UTILS_C------------------------------------------------------------------
*/
int			pass_redir(char *tmp, int i);
int			pass_quote(char *cmd, int i, int cut);
/*
REDIRECTION_UTILS_C--------------------------------------------------------------
*/
char		*ft_place_redir(char *str);
int			ft_count_redirection(char *str, char c_redirect);
void		init_redir_zero(t_command	*(*table_pipe), int number_pipe);

/*
REDIRECTION_C--------------------------------------------------------------------
*/
t_command	**ft_redirection_init(t_command	*(*table_pipe), int number_pipe);
void		ft_parse_redir_in(t_command *(*table_pp), int nb_pp, char c, int i);
void		ft_parse_redir_ou(t_command *(*table_pp), int nb_pp, char c, int i);
char		*ft_search_redir(char *str, char c);
/*
FUSION_TAB_REDIR_C---------------------------------------------------------------
*/
void		fusion_tab_redir(t_command	*(*table_pipe));

/*
PARSING_UTILS_C------------------------------------------------------------------
*/

/*
PARSING_C------------------------------------------------------------------------
*/
int			ft_count_pipe(char *line);
t_command	**ft_parse_pipe(t_command *(*table_pipe), char *line);
int			ft_doubletab_len(char **tab);
t_command	**ft_parsing(t_data *data, char *line, t_command *(*table_pipe));
/*
TOKENIZER_C----------------------------------------------------------------------
*/
int			check_builtin(char *str);
int			struc_len(t_command **table_pipe);
void		tokenizer_cmd(t_command **table_pipe, int nb_pp, t_data *data);
void		tokenizer_redir_in(t_command **table_pipe, int np);
void		tokenizer_redir_out(t_command **table_pipe, int np);

/*
TOKENIZER_2_C--------------------------------------------------------------------
*/
char		token_quote(t_command **t_p, int nb_pp, int i);

/*
FREE-----------------------------------------------------------------------------
*/
void		ft_free_doutab(char **tab);
void		free_struc(t_command **table_pipe);

/*
SIGNAL_C-------------------------------------------------------------------------
*/
void		ft_signal(int sig, siginfo_t *info, void *context);
void		sig_int(int sig, siginfo_t *info, void *context);
void		sig_quit(int sig, siginfo_t *info, void *context);
void		signal_init(void);

/*
SPLIT_PIPE_C---------------------------------------------------------------------
*/
char		**split_pipe(char *str);

/*
VERIF_LINE_UTILS_C---------------------------------------------------------------
*/
int			error_msg(char *line);
int			error_msg_signal(char *msg);
int			pass_quote_verif_line(char *line, int i);

/*
VERIF_LINE_C---------------------------------------------------------------------
*/
int			verif_quote(char *line);
int			verif_pipe(char *line, int *i);
int			verif_redir_syntax(char *line);
int			verif_line(char *line);

/*
VERIF_LINE_C---------------------------------------------------------------------
*/
void		go_expand(t_data *data, t_command *(*table_pipe));

/*
PARSE_QUOTE_C--------------------------------------------------------------------
*/
char		*parse_str_quote(char *str);
void		parse_quote_redir(char **tab);
void		parse_quote(t_command *(*table_pipe));

/*
PARSE_BACK_C---------------------------------------------------------------------
*/
char		*parse_str_back_slash(char *str);
void		parse_back_redir(char **tab, char **tab_token);
void		parse_back_slash(t_command *(*table_pipe));

void		status_child(int child);
#endif
