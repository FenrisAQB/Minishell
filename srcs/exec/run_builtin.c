/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:02:09 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/26 15:40:51 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check for builtin commands
 *
 * @param e The execution node
 * @return int The token of the builtin command
 */
int	is_builtin(t_exec *e)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(e->cmd[0], "echo", 5))
		ret = TOKEN_ECHO;
	if (!ft_strncmp(e->cmd[0], "cd", 3))
		ret = TOKEN_CD;
	if (!ft_strncmp(e->cmd[0], "pwd", 4))
		ret = TOKEN_PWD;
	if (!ft_strncmp(e->cmd[0], "export", 7))
		ret = TOKEN_EXPORT;
	if (!ft_strncmp(e->cmd[0], "unset", 6))
		ret = TOKEN_UNSET;
	if (!ft_strncmp(e->cmd[0], "env", 4))
		ret = TOKEN_ENV;
	if (!ft_strncmp(e->cmd[0], "exit", 5))
		ret = TOKEN_EXIT;
	if (ft_strchr(e->cmd[0], '='))
		ret = TOKEN_VAR;
	return (ret);
}

/**
 * @brief Run the builtin command
 *
 * @param data The main data structure
 * @param e The execution node
 */
void	run_builtin(t_data *data, t_exec *e)
{
	int	type;

	type = is_builtin(e);
	if (type == TOKEN_ECHO)
		run_echo(data, e);
	if (type == TOKEN_CD)
		run_cd(data, e);
	if (type == TOKEN_PWD)
		builtin_pwd(data);
	if (type == TOKEN_EXPORT)
		run_export(data, e);
	if (type == TOKEN_UNSET)
		run_unset(data, e);
	if (type == TOKEN_ENV)
		run_env(data, e);
	if (type == TOKEN_EXIT)
		builtin_exit(data, e);
	if (type == TOKEN_VAR)
		run_var(data, e, 0);
}

/**
 * @brief Run the command if no pipe
 *
 * @param data The main data structure
 * @param cmd The command node
 */
void	run_no_pipe(t_data *data, t_cmd *cmd)
{
	if (!cmd || g_here_doc_exit)
		return ;
	if (cmd->type == TOKEN_REDIR)
		redir_cmd_for_builtin(data, (t_redir *) cmd);
	else if (cmd->type == TOKEN_EXEC)
	{
		run_builtin(data, (t_exec *) cmd);
		dup2(data->fd_out, 1);
		dup2(data->fd_in, 0);
	}
}
