/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:27:54 by aptive            #+#    #+#             */
/*   Updated: 2022/07/04 19:51:55 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Quand bash fonctionne de manière interactive, il ignore le signal SIGTERM (c'est pourquoi kill 0 ne tue pas un shell interactif), et le signal SIGINT est intercepté et géré (c'est pourquoi la commande interne wait n'est pas interruptible). Dans tous les cas, bash ignore le signal SIGQUIT. Si le contrôle de jobs est disponible, bash ignore les signaux SIGTTIN, SIGTTOU, et SIGTSTP.
Les commandes externes lancées par bash reçoivent les valeurs des signaux héritées par le shell de leur parent. Quand le contrôle de job n'est pas actif, les jobs en arrière-plan ignorent les signaux SIGINT et SIGQUIT en plus des gestionnaires hérités. Les commandes exécutées en tant que résultat de la substitution de commandes ignorent les signaux de contrôle de jobs émis par le clavier SIGTTIN, SIGTTOU, et SIGTSTP.

Par défaut, le shell se termine à la réception de SIGHUP. Avant de se terminer, un shell interactif renvoie SIGHUP à tous les jobs en cours ou arrêtés. Les jobs arrêtés reçoivent aussi SIGCONT pour s'assurer qu'il recevront bien le SIGHUP. Pour empêcher le shell d'envoyer ce signal à un job particulier, il faut le retirer de la table des jobs à l'aide de la commande interne disown (voir FONCTIONS INTERNES DU SHELL plus bas) ou le marquer comme exempté de SIGHUP avec disown -h.

Si l'option du shell huponexit a été activée avec la fonction shopt, bash envoie un signal SIGHUP à tous les jobs lorsqu'un shell de login interactif se termine.

Lorsque bash attend la fin d'une commande et qu'il reçoit un signal qu'il doit capturer, le gestionnaire de signal ne sera pas exécuté avant que la commande soit finie. Lorsque bash attend la fin d'une commande asynchrone avec wait la réception d'un signal capturé causera la fin immédiate de la commande wait avec un code de retour supérieur à 128, à la suite de quoi le gestionnaire de signal sera exécuté.
*/
void	ft_signal(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	if (sig == SIGQUIT)
		sig_quit(sig, info, context);
	else if (sig == SIGINT)
		sig_int(sig, info, context);
}

void	sig_quit(int sig, siginfo_t *info, void *context)
{
	ft_putstr_fd("\b\b  \b\b", STDERR);
}

void	sig_int(int sig, siginfo_t *info, void *context)
{
	ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_putstr_fd("\n", STDERR);
	ft_putstr_fd("minishell: ", STDERR);
}
// Interruption (ctrl-C) == sigint == Terminaison int sig 2
// Interruption forte (ctrl-\)	 == sigquit == Terminaison + core dump int sig 3

void	signal_init(void)
{
	// g_signal.quit = 0;
	// g_signal.sigint = 0;
	g_signal.nt_status = 0;
	g_signal.status = 0;
}
