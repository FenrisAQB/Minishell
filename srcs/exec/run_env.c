/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:57:55 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/23 16:32:27 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Run the env command
 *
 * @param data The main data structure
 * @param e The execution node
 */
void	run_env(t_data *data, t_exec *e)
{
	if (find_env_var("PATH=", data->env) == get_env_len(data->env))
	{
		if (data->is_pipe)
			clean_exit(data, "env: No such file or directory", 2, 127);
		error_message("env: No such file or directory", 2, 127);
	}
	else if (e->cmd[1])
	{
		if (data->is_pipe)
			clean_exit(data, NULL, 2, EXIT_FAILURE);
		getset_exit_code(EXIT_FAILURE);
		return ;
	}
	else
		builtin_env(data);
	if (data->is_pipe)
		clean_exit(data, NULL, 1, EXIT_SUCCESS);
	getset_exit_code(EXIT_SUCCESS);
}
