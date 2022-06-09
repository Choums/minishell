/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:19:48 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/09 16:18:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Permet de retrouver le fichier bin de la commande donnee et verifie
 *		ses droits.
 *	Ajoute "/[filename]" a chaque path de la lst
*/
char	*find_bin(t_list *lst_path, char *bin)
{
	char	*dir;
	char	*path;

	while (lst_path)
	{
		dir = ft_strjoin(lst_path->content, "/");
		path = ft_strjoin(dir, bin);
		free(dir);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		lst_path = lst_path->next;
	}
	return (NULL);
}

/*
 *	Child processus
 *	Trouve le path de la commande et l'execute
 *	Si 1er process, doit ouvrir le fichier en input et check
 *
*/
void	process(t_data *data, t_command *cmd)
{
	char	*path;
	char	**env;

	env = lst_dup(data->h_env);
	if (cmd->tab_redir)
		redir(data, cmd->tab_redir);
	path = find_bin(data->path, cmd->tab_cmd[0]);
	// if (!cmd->tab_redir)
	// 	redir_pipe();
	printf("in\n");
	if (execve(path, cmd->tab_cmd, env) > 0)
		return ;
}

/*
 *	Cree des processus enfant pour chaque commandes ainsi que les pipes
 *	Les process s'executent en meme temps
 *	-------------------------------------
 *	Ordre des process
 *	2 a la fois
 *	echo salut > outfile | wc -l >> outfile | cat | ls
 *	echo et wc on ecrit dans le outfile
 *	PAR CONTRE ls devance le cat et affiche les fichers 
 *		dont outfile avec les ecritures
 *	-------------------------------------
 *	double redir
 *	echo salut > infile > outfile
 *	les 2 fichiers sont crees
 *	salut n'est ecrit que dans outfile
 *	ouverture et redir de gauche a droite
 *	-------------------------------------
 *	builtin
 *	cd ~ | ls (dans un dossier autre que le HOME)
 *	le 1er process se rend au HOME mais ls affiche le dossier actuel
 *	echo salut
 *	la commande est executé via sa fontion dans le process parent
 *	echo salut | wc
 *	les 2 cmd sont fork, en cas de pipe les builtins ont leur propre process
*/
void	mother_board(t_data *data, t_command **cmd)
{
	pid_t	child;

	if (is_builtin(cmd) && get_double_tab_len(cmd) == 1)
		run_builtin(data, cmd[0]);
	else if (!is_builtin(cmd) && get_double_tab_len(cmd) == 1)
	{
		child = fork();
		if (child == 0)
			process(data, cmd[0]);
		waitpid(0, NULL, 0);
	}
	else
	{
		
	}
}

int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->tab_cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->tab_cmd[0], "exit") == 0)
		return (1);
	else
		return (0);
}

void	run_builtin(t_data *data, t_command *cmd)
{
	if (ft_strcmp(cmd->tab_cmd[0], "echo") == 0)
		echo(cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "cd") == 0)
		change_dir(data->h_env, cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->tab_cmd[0], "export") == 0)
		export(data, cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "unset") == 0)
		unset(data, cmd->tab_cmd);
	else if (ft_strcmp(cmd->tab_cmd[0], "env") == 0)
		print_env(data->h_env);
	else if (ft_strcmp(cmd->tab_cmd[0], "exit") == 0)
		is_exit(data, cmd->tab_cmd[0]);
}
