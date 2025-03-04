/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:10:55 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/27 13:40:45 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Run the command
 *
 * @param data The main data structure
 * @param cmd The command to run
 */
void	run_cmd(t_data *data, t_cmd *cmd)
{
	db_print_tree(cmd, "After entering run_cmd", BGREEN);
	if (!cmd)
		return ;
	if (cmd->type == TOKEN_EXEC)
	{
		setup_signal(2);
		exec_cmd(data, (t_exec *)cmd, NULL, NULL);
	}
	else if (cmd->type == TOKEN_REDIR)
		redir_cmd(data, (t_redir *)cmd);
	else if (cmd->type == TOKEN_PIPE)
		pipe_cmd(data, (t_pipe *)cmd);
	clean_exit(data, NULL, 1, EXIT_SUCCESS);
}
