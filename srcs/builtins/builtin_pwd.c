/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:01:32 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/18 13:18:00 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Print the current working directory
 *
 * @param data The main data structure
 */
void	builtin_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (data->is_pipe)
			clean_exit(data, "PWD not found", 2, EXIT_FAILURE);
		error_message("PWD not found", 2, EXIT_FAILURE);
		return ;
	}
	else
	{
		ft_putendl_fd(cwd, 1);
		free_and_null(cwd);
	}
	if (data->is_pipe)
		clean_exit(data, NULL, 1, EXIT_SUCCESS);
	getset_exit_code(EXIT_SUCCESS);
}
