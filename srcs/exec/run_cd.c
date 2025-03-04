/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:11:32 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/18 15:15:05 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Run the cd command
 *
 * @param data The main data structure
 * @param e The execution node
 */
void	run_cd(t_data *data, t_exec *e)
{
	int	ret;

	ret = 0;
	if (e->cmd[1] && e->cmd[2])
	{
		if (data->is_pipe)
			clean_exit(data, "minishell: cd: too many arguments", 2, 1);
		error_message("minishell: cd: too many arguments", 2, 1);
		return ;
	}
	if (!e->cmd[1])
		ret = builtin_cd(data, NULL);
	else if (e->cmd[1])
		ret = builtin_cd(data, e->cmd[1]);
	if (ret == -1)
	{
		if (data->is_pipe)
			clean_exit(data, NULL, 1, EXIT_FAILURE);
		getset_exit_code(EXIT_FAILURE);
		return ;
	}
	if (data->is_pipe)
		clean_exit(data, NULL, 1, EXIT_SUCCESS);
	getset_exit_code(EXIT_SUCCESS);
}
