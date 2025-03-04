/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:01:43 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/23 16:31:49 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Get the string to echo
 *
 * @param data The data structure
 * @param args The arguments array
 */
static char	*get_echo_str(t_data *data, t_exec *e, int i)
{
	char	*str;
	char	*tmp;

	str = ft_strdup(e->cmd[i]);
	if (!str)
		clean_exit(data, "Malloc: run_echo:30", 2, EXIT_FAILURE);
	while (e->cmd[i])
	{
		if (e->cmd[i + 1])
		{
			tmp = ft_strjoin(str, " ");
			free_and_null(str);
			if (!tmp)
				clean_exit(data, "Malloc: run_echo:38", 2, EXIT_FAILURE);
			str = ft_strjoin(tmp, e->cmd[i + 1]);
			free_and_null(tmp);
			if (!str)
				clean_exit(data, "Malloc: run_echo:42", 2, EXIT_FAILURE);
		}
		i++;
	}
	return (str);
}

/**
 * @brief Check if the argument is a newline
 *
 * @param str The argument
 * @return int 0 if it is a newline, 1 otherwise
 */
static int	is_newline(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Run the echo command
 *
 * @param data The data structure
 * @param args The arguments array
 */
void	run_echo(t_data *data, t_exec *e)
{
	char	*str;
	int		nl;
	int		i;

	nl = 1;
	i = 1;
	while (e->cmd[i] && is_newline(e->cmd[i]))
	{
		nl = 0;
		i++;
	}
	if (!e->cmd[i])
		str = NULL;
	else if (e->cmd[i] && e->cmd[i + 1])
		str = get_echo_str(data, e, i);
	else if (e->cmd[i] && !e->cmd[i + 1])
	{
		str = ft_strdup(e->cmd[i]);
		if (!str)
			clean_exit(data, "Malloc: run_echo:76", 2, EXIT_FAILURE);
	}
	builtin_echo(str, nl);
	if (data->is_pipe)
		clean_exit(data, NULL, 1, EXIT_SUCCESS);
	getset_exit_code(EXIT_SUCCESS);
}
