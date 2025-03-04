/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:30:11 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/26 13:22:45 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if the variable is valid
 *
 * @param var The variable
 * @return int 1 if valid, 0 otherwise
 */
static int	is_valid(char *var)
{
	int	i;

	i = 0;
	if (var[i] == '=' || ft_isdigit(var[i]))
		return (0);
	while (i < (int)ft_strlen(var) - 1)
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Handle the arguments of the export command
 *
 * @param data The main data structure
 * @param e The execution node
 * @param error The error flag
 * @return int The error flag
 */
static int	handle_args(t_data *data, t_exec *e, int error)
{
	int		i;
	char	*var;
	char	*content;

	i = 1;
	while (e->cmd[i])
	{
		var = extract_var(e->cmd[i], data);
		content = extract_content(e->cmd[i++], var, data);
		if (ft_strnstr(var, "+=", ft_strlen(var)))
		{
			var = trim_plus(var, content, data);
			content = join_content(var, content, data);
		}
		if (is_valid(var))
			update_env(var, content, data->env, data);
		else
		{
			error = 1;
			free_and_null(var);
			free_and_null(content);
			error_message("export: not a valid identifier", 2, EXIT_FAILURE);
		}
	}
	return (error);
}

/**
 * @brief Run the export command
 *
 * @param data The main data structure
 * @param e The execution node
 */
void	run_export(t_data *data, t_exec *e)
{
	int	error;

	error = 0;
	if (!e->cmd[1])
		builtin_export(data, NULL, NULL);
	else
		error = handle_args(data, e, error);
	if (error)
	{
		if (data->is_pipe)
			clean_exit(data, NULL, 1, EXIT_FAILURE);
		getset_exit_code(EXIT_FAILURE);
	}
	else
	{
		if (data->is_pipe)
			clean_exit(data, NULL, 1, EXIT_SUCCESS);
		getset_exit_code(EXIT_SUCCESS);
	}
}
