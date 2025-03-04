/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:49:15 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/18 13:14:28 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Run the unset command
 *
 * @param data The main data structure
 * @param e The exec node
 */
void	run_unset(t_data *data, t_exec *e)
{
	int	i;

	i = 0;
	if (e->cmd[1])
	{
		while (e->cmd[++i])
			builtin_unset(data, e->cmd[i]);
	}
	if (data->is_pipe)
		clean_exit(data, NULL, 0, EXIT_SUCCESS);
	getset_exit_code(EXIT_SUCCESS);
}
