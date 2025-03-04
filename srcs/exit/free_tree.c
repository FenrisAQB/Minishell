/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:47:29 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/26 17:58:13 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees everything inside the pipe node and under
 *
 * @param pipe The pointer to the pipe structure
 */
static void	free_from_pipe(t_pipe *pipe)
{
	if (!pipe)
		return ;
	if (pipe->left)
		free_from_cmd(pipe->left);
	if (pipe->right)
		free_from_cmd(pipe->right);
	free_and_null(pipe);
}

/**
 * @brief Frees everything inside the redir node and under
 *
 * @param redir The pointer to the redir structure
 */
static void	free_from_redir(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->cmd)
		free_from_cmd(redir->cmd);
	if (redir->file)
		free_and_null(redir->file);
	if (redir->fd != -1)
		close(redir->fd);
	free_and_null(redir);
}

/**
 * @brief Frees everything inside the exec node
 *
 * @param exec The pointer to the exec structure
 */
static void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->full_cmd)
		free_and_null(exec->full_cmd);
	if (exec->cmd)
		free_tab(exec->cmd, 0);
	free_and_null(exec);
}

/**
 * @brief Frees everything from the passed command pointer and under
 *
 * @param cmd The pointer to the command structure
 */
void	free_from_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == TOKEN_PIPE)
		free_from_pipe((t_pipe *)cmd);
	else if (cmd->type == TOKEN_REDIR)
		free_from_redir((t_redir *)cmd);
	else if (cmd->type == TOKEN_EXEC)
		free_exec((t_exec *)cmd);
}
