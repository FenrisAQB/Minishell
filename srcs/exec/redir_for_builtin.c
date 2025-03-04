/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_for_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:16:05 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/26 18:57:38 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Run a single input redir in case of single builtin
 *
 * @param data The main data structure
 * @param r The redir node
 * @param last 1 if it is the last redir of the same kind, 0 otherwise
 * @param exec 1 if the command should be executed, 0 otherwise
 */
static int	redir_sl_fb(t_data *data, t_redir *r, int last, int exec)
{
	if (access(r->file, R_OK) == -1)
		return (error_message("no such file or directory", 2, EXIT_FAILURE), 1);
	if (last && exec)
	{
		r->fd = open(r->file, O_RDONLY);
		if (r->fd < 0)
			return (error_message("opening fd", 2, EXIT_FAILURE), 1);
		if (dup2(r->fd, 0) < 0)
			return (close(r->fd), error_message("fd duplication", 2, 1), 1);
	}
	close(r->fd);
	run_no_pipe(data, r->cmd);
	return (0);
}

/**
 * @brief Run a single output redir in case of single builtin
 *
 * @param data The main data structure
 * @param r The redir node
 * @param last 1 if it is the last redir of the same kind, 0 otherwise
 * @param exec 1 if the command should be executed, 0 otherwise
 */
static int	redir_sr_fb(t_data *data, t_redir *r, int last, int exec)
{
	r->fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (r->fd < 0)
		return (error_message("opening fd", 2, EXIT_FAILURE), 1);
	if (last && exec)
	{
		if (dup2(r->fd, 1) < 0)
			return (close(r->fd), error_message("fd duplication", 2, 1), 1);
	}
	close(r->fd);
	run_no_pipe(data, r->cmd);
	return (0);
}

/**
 * @brief Run a double input redir (here_doc) in case of single builtin
 *
 * @param data The main data structure
 * @param r The redir node
 * @param last 1 if it is the last redir of the same kind, 0 otherwise
 * @param exec 1 if the command should be executed, 0 otherwise
 */
static int	redir_dl_fb(t_data *data, t_redir *r, int last, int exec)
{
	if (last && exec && !g_here_doc_exit)
	{
		if (dup2(r->fd, 0) < 0)
			return (close(r->fd), error_message("fd duplication", 2, 1), 1);
	}
	close(r->fd);
	run_no_pipe(data, r->cmd);
	return (0);
}

/** @brief Run a double output redir in case of single builtin
*
* @param data The main data structure
* @param r The redir node
* @param last 1 if it is the last redir of the same kind, 0 otherwise
* @param exec 1 if the command should be executed, 0 otherwise
*/
static int	redir_dr_fb(t_data *data, t_redir *r, int last, int exec)
{
	r->fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (r->fd < 0)
		return (error_message("opening fd", 2, EXIT_FAILURE), 1);
	if (last && exec)
	{
		if (dup2(r->fd, 1) < 0)
			return (close(r->fd), error_message("fd duplication", 2, 1), 1);
	}
	close(r->fd);
	run_no_pipe(data, r->cmd);
	return (0);
}

/**
 * @brief Run the redirection command
 *
 * @param data The main data structure
 * @param r The redir node
 */
void	redir_cmd_for_builtin(t_data *data, t_redir *r)
{
	int	last_redir;
	int	exec_present;

	db_print_str("redir_cmd_for_builtin", "In", BBLUE);
	db_print_tree((t_cmd *)r, 0, 0);
	if (!r || r->type != TOKEN_REDIR)
		return ;
	last_redir = last_redir_of_kind(r, r->in_out);
	exec_present = exec_in_branch(r);
	if (r->in_out == TOKEN_REDIR_SL)
		redir_sl_fb(data, r, last_redir, exec_present);
	else if (r->in_out == TOKEN_REDIR_SR)
		redir_sr_fb(data, r, last_redir, exec_present);
	else if (r->in_out == TOKEN_REDIR_DL)
		redir_dl_fb(data, r, last_redir, exec_present);
	else if (r->in_out == TOKEN_REDIR_DR)
		redir_dr_fb(data, r, last_redir, exec_present);
}
