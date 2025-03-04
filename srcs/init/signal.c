/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:40:29 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/26 13:42:57 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handles signals for the parent
 * 
 * @param sig
 */
static void	parent_sa(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @brief Handles signals for the child
 * 
 * @param sig
 */
static void	child_sa(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

/**
 * @brief Handles signals for here_docs
 * 
 * @param sig
 */
static void	here_doc_sa(int sig)
{
	(void)sig;
	g_here_doc_exit = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	close(0);
}

/**
 * @brief Sets up signal handling
 * 
 * @param mode Different use cases
 */
void	setup_signal(int mode)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	ft_memset(&sig_int, 0, sizeof(struct sigaction));
	ft_memset(&sig_quit, 0, sizeof(struct sigaction));
	sig_quit.sa_handler = SIG_IGN;
	if (mode == 0)
		sig_int.sa_handler = &parent_sa;
	else if (mode == 1)
		sig_int.sa_handler = SIG_IGN;
	else if (mode == 2)
	{
		sig_int.sa_handler = &child_sa;
		sig_quit.sa_handler = &child_sa;
	}
	else if (mode == 3)
		sig_int.sa_handler = &here_doc_sa;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
