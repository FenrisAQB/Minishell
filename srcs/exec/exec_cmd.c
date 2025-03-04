/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:10:49 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/27 13:54:04 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Add slash to the path
 *
 * @param paths The path array
 * @return char** The path array with a slash at the end
 */
static char	**add_slash(t_data *data, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			clean_exit(data, "Malloc: exec_cmd:31", 2, EXIT_FAILURE);
		free_and_null(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (paths);
}

/**
 * @brief Get the paths object from the environment array
 * @details Find path, trim it, split it and add a slash at the end
 * @param data The main data structure
 */
static char	**get_paths(t_data *data)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = 0;
	paths = NULL;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PATH=", 5) && data->env[i][5])
		{
			tmp = ft_strtrim(data->env[i], "PATH=");
			if (!tmp)
				clean_exit(data, "Malloc: exec_cmd:27", 2, EXIT_FAILURE);
			paths = ft_split(tmp, ':');
			free_and_null(tmp);
		}
		i++;
	}
	if (!paths)
		return (NULL);
	paths = add_slash(data, paths);
	return (paths);
}

/**
 * @brief Get the absolut command path
 *
 * @param data The main data structure
 * @param e The execution node
 * @return the full command path if found
 */
static char	*get_full_cmd(t_data *data, t_exec *e)
{
	char	*tmp;
	char	**paths;

	if (e->full_cmd[0] && ft_strchr(e->full_cmd, '/'))
	{
		tmp = ft_strdup(e->full_cmd);
		if (!tmp)
			clean_exit(data, "Malloc: exec_cmd:27", 2, EXIT_FAILURE);
		return (tmp);
	}
	paths = get_paths(data);
	tmp = find_cmd(data, e, paths);
	if (!tmp)
		return (clean_exit(data, "Command not found", 2, 127), NULL);
	return (tmp);
}

/**
 * @brief Copy a tab of strings
 *
 * @param arr The tab to copy
 * @return the copied tab
 */
static char	**cp_tab(char **arr)
{
	int		i;
	char	**ret;

	i = 0;
	while (arr[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		if (!ret[i])
		{
			free_mid_tab(ret, i - 1);
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/**
 * @brief Execute a command from an exec node
 *
 * @param data The main data structure
 * @param e The execution node
 */
void	exec_cmd(t_data *data, t_exec *e, char *abs_cmd, char **argv)
{
	db_print_str("exec_cmd", "In", BBLUE);
	db_print_tree((t_cmd *)e, 0, 0);
	if (is_builtin(e))
		run_builtin(data, e);
	abs_cmd = get_full_cmd(data, e);
	argv = cp_tab(e->cmd);
	if (!argv)
	{
		free(abs_cmd);
		clean_exit(data, "Malloc: exec_cmd:80", 2, EXIT_FAILURE);
	}
	free_before_exit(data);
	if (execve(abs_cmd, argv, data->env) < 0)
	{
		free_tab(argv, 0);
		free_tab(data->env, 0);
		if (!access(abs_cmd, F_OK) && access(abs_cmd, X_OK) < 0)
		{
			free(abs_cmd);
			clean_exit(NULL, "Permission denied", 2, 126);
		}
		free(abs_cmd);
		clean_exit(NULL, "Command not found", 2, 127);
	}
}
