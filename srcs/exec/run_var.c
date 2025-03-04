/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:25:57 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/23 16:32:31 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handle the case where the variable is not found
 *
 * @param var The variable name
 * @param content The variable content
 * @param data The main data structure
 * @param e The execution node
 */
static void	handle_no_var(char *var, char *content, t_data *data, t_exec *e)
{
	free_and_null(var);
	free_and_null(content);
	if (data->is_pipe && !e->cmd[1])
		clean_exit(data, NULL, 1, EXIT_SUCCESS);
	else if (!data->is_pipe && !e->cmd[1])
		return ;
}

/**
 * @brief Run variable assignations without export
 *
 * @param data The main data structure
 * @param e The execution node
 */
void	run_var(t_data *data, t_exec *e, int i)
{
	char	*var;
	char	*content;

	while (e->cmd[i])
	{
		var = extract_var(e->cmd[i], data);
		content = extract_content(e->cmd[i++], var, data);
		if (ft_strchr(var, '+'))
		{
			var = trim_plus(var, content, data);
			content = join_content(var, content, data);
		}
		if (find_env_var(var, data->env) == get_env_len(data->env))
		{
			handle_no_var(var, content, data, e);
			continue ;
		}
		update_env(var, content, data->env, data);
	}
	if (data->is_pipe)
		clean_exit(data, NULL, 1, EXIT_SUCCESS);
	getset_exit_code(EXIT_SUCCESS);
}
