/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:01:58 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/26 18:57:24 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Run a single input redir
 *
 * @param data The main data structure
 * @param r The redir node
 * @param last 1 if it is the last redir of the same kind, 0 otherwise
 * @param exec 1 if the command should be executed, 0 otherwise
 */
static void	redir_sl(t_data *data, t_redir *r, int last, int exec)
{
	if (access(r->file, R_OK) == -1)
		clean_exit(data, "no such file or directory", 2, EXIT_FAILURE);
	if (last && exec)
	{
		r->fd = open(r->file, O_RDONLY);
		if (r->fd < 0)
			clean_exit(data, "opening fd", 2, EXIT_FAILURE);
		if (dup2(r->fd, 0) < 0)
			clean_cmd_exit(data, r->fd, -1, "fd duplication");
	}
	close(r->fd);
	run_cmd(data, r->cmd);
}

/**
 * @brief Run a single output redir
 *
 * @param data The main data structure
 * @param r The redir node
 * @param last 1 if it is the last redir of the same kind, 0 otherwise
 * @param exec 1 if the command should be executed, 0 otherwise
 */
static void	redir_sr(t_data *data, t_redir *r, int last, int exec)
{
	r->fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (r->fd < 0)
		clean_exit(data, "opening fd", 2, EXIT_FAILURE);
	if (last && exec)
	{
		if (dup2(r->fd, 1) < 0)
			clean_cmd_exit(data, -1, r->fd, "fd duplication");
	}
	close(r->fd);
	run_cmd(data, r->cmd);
}

/**
 * @brief Run a double input redir (here_doc)
 *
 * @param data The main data structure
 * @param r The redir node
 * @param last 1 if it is the last redir of the same kind, 0 otherwise
 * @param exec 1 if the command should be executed, 0 otherwise
 */
static void	redir_dl(t_data *data, t_redir *r, int last, int exec)
{
	if (last && exec)
	{
		if (dup2(r->fd, 0) < 0)
			clean_cmd_exit(data, r->fd, 0, "fd duplication");
	}
	close(r->fd);
	run_cmd(data, r->cmd);
}

/** @brief Run a double output redir
*
* @param data The main data structure
* @param r The redir node
* @param last 1 if it is the last redir of the same kind, 0 otherwise
* @param exec 1 if the command should be executed, 0 otherwise
*/
static void	redir_dr(t_data *data, t_redir *r, int last, int exec)
{
	r->fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (r->fd < 0)
		clean_exit(data, "opening fd", 2, EXIT_FAILURE);
	if (last && exec)
	{
		if (dup2(r->fd, 1) < 0)
			clean_cmd_exit(data, -1, r->fd, "fd duplication");
	}
	close(r->fd);
	run_cmd(data, r->cmd);
}

/**
 * @brief Run the redirection command
 *
 * @param data The main data structure
 * @param r The redir node
 */
void	redir_cmd(t_data *data, t_redir *r)
{
	int	last_redir;
	int	exec_present;

	db_print_str("redir_cmd", "In", BBLUE);
	db_print_tree((t_cmd *)r, 0, 0);
	last_redir = last_redir_of_kind(r, r->in_out);
	exec_present = exec_in_branch(r);
	if (r->in_out == TOKEN_REDIR_SL)
		redir_sl(data, r, last_redir, exec_present);
	else if (r->in_out == TOKEN_REDIR_SR)
		redir_sr(data, r, last_redir, exec_present);
	else if (r->in_out == TOKEN_REDIR_DL)
		redir_dl(data, r, last_redir, exec_present);
	else if (r->in_out == TOKEN_REDIR_DR)
		redir_dr(data, r, last_redir, exec_present);
}
