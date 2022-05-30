/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:39:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/30 19:57:50 by tdelauna         ###   ########.fr       */
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


typedef struct s_redirection
{
	char	**in;
	char	**token_in;
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
int		ft_count_redirection(char *str, char c_redirect);
t_command	**ft_redirection_init(t_command	*(*table_pipe), int number_pipe);
void	ft_parse_redir_in(t_command *(*table_pp), int nb_pp, char c);
void	ft_parse_redir_out(t_command *(*table_pp), int nb_pp, char c);

/*
PARSING_C------------------------------------------------------------------------
*/
int		ft_count_pipe(char *line);
t_command	**ft_parse_pipe(t_command	*(*table_pipe), char *line);
void	ft_free_doutab(char **tab);
int		ft_doubletab_len(char **tab);
void	ft_parsing(char *line);
/*
TOKENIZER_C----------------------------------------------------------------------
*/
void	tokenizer_cmd(t_command **table_pipe, int nb_pp);
#endif
