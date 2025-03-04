/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:58:38 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/23 16:30:54 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if the redir is the last of its type
 *
 * @param redir The redir node
 * @param token The token of the redir
 * @return int 1 if not last, 0 if last
 */
int	last_redir_of_kind(t_redir *redir, int token)
{
	while (1)
	{
		if (!redir->cmd || (redir->cmd && redir->cmd->type != TOKEN_REDIR))
			break ;
		redir = (t_redir *)redir->cmd;
		if (token == 8 || token == 10)
		{
			if (redir->in_out == 8 || redir->in_out == 10)
				return (0);
		}
		else if (token == 9 || token == 11)
		{
			if (redir->in_out == 9 || redir->in_out == 11)
				return (0);
		}
	}
	return (1);
}

/**
 * @brief Check if next node is a redir
 *
 * @param redir the redir node
 * @return int 0 if next is redir, 1 if not
 */
int	exec_in_branch(t_redir *redir)
{
	while (redir && redir->cmd)
	{
		if (redir->cmd->type == TOKEN_EXEC)
			return (1);
		redir = (t_redir *)redir->cmd;
	}
	return (0);
}

/**
 * @brief Check if the command is a single builtin (no pipe)
 *
 * @param cmd The command node
 * @return int 1 if builtin without pipe, 0 if not
 */
int	is_only_builtin(t_cmd *cmd)
{
	t_exec	*e;
	t_redir	*r;

	e = NULL;
	while (cmd)
	{
		if (cmd->type == TOKEN_PIPE)
			return (0);
		if (cmd->type == TOKEN_REDIR)
		{
			r = (t_redir *)cmd;
			cmd = r->cmd;
		}
		else if (cmd->type == TOKEN_EXEC)
		{
			e = (t_exec *)cmd;
			break ;
		}
	}
	if (!e)
		return (0);
	if (!is_builtin(e))
		return (0);
	return (1);
}
