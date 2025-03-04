/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:57:33 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/23 16:29:29 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handles the case cd -
 *
 * @param data the main data structure
 * @return int -1 if an error occured, 0 otherwise
 */
static int	handle_minus(t_data *data)
{
	char	*tmp;
	int		i;

	i = find_env_var("OLDPWD=", data->env);
	if (i == get_env_len(data->env))
	{
		error_message("minishell: cd: OLDPWD not set", 2, EXIT_FAILURE);
		return (-1);
	}
	tmp = ft_strtrim(data->env[i], "OLDPWD=");
	if (!tmp)
		clean_exit(data, "Malloc: builtin_cd:28", 2, EXIT_FAILURE);
	if (chdir(tmp) == -1)
	{
		err_msg_cd(tmp, data);
		free_and_null(tmp);
		return (-1);
	}
	ft_putendl_fd(tmp, 1);
	free_and_null(tmp);
	return (0);
}

/**
 * @brief Handle the case where there is no path given as an argument
 * @details Change the current working directory to the home directory
 * @param data The main data structure
 */
static int	handle_no_args(t_data *data)
{
	char	*home;
	int		i;

	i = find_env_var("HOME=", data->env);
	if (i == get_env_len(data->env))
	{
		error_message("minishell: cd: HOME not set", 2, EXIT_FAILURE);
		return (-1);
	}
	home = ft_strtrim(data->env[i], "HOME=");
	if (!home)
		clean_exit(data, "Malloc: builtin_cd:34", 2, EXIT_FAILURE);
	if (chdir(home) == -1)
	{
		err_msg_cd(home, data);
		free_and_null(home);
		return (-1);
	}
	free_and_null(home);
	return (0);
}

/**
 * @brief Handle the case where the PWD variable is not set
 * @details Set the OLDPWD variable to the previous working directory
 * @param data The main data structure
 */
static void	handle_no_pwd(t_data *data)
{
	char	*old_cwd;
	char	*var;

	if (find_env_var("OLDPWD=", data->env) != get_env_len(data->env))
	{
		var = ft_strdup("OLDPWD=");
		if (!data->cwd)
			old_cwd = ft_strdup("");
		else
			old_cwd = ft_strdup(data->cwd);
		if (!old_cwd || !var)
		{
			free_and_null(var);
			free_and_null(old_cwd);
			clean_exit(data, "Malloc: builtin_cd:66", 2, EXIT_FAILURE);
		}
		update_env(var, old_cwd, data->env, data);
	}
	free_and_null(data->cwd);
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		clean_exit(data, "Malloc: builtin_cd:73", 2, EXIT_FAILURE);
}

/**
 * @brief Handle the case where the PWD variable is set
 * @details Set the PWD variable to the current working directory
 * @param data The main data structure
 */
static void	handle_if_pwd(t_data *data)
{
	char	*cwd;
	char	*var;

	var = ft_strdup("PWD=");
	cwd = getcwd(NULL, 0);
	if (!cwd || !var)
	{
		free_and_null(cwd);
		free_and_null(var);
		clean_exit(data, "Malloc: builtin_cd:92", 2, EXIT_FAILURE);
	}
	update_env(var, cwd, data->env, data);
	handle_no_pwd(data);
}

/**
 * @brief Change the current working directory
 * @details Change the current working directory to the given path
 * @param data The main data structure
 * @param path The path to change to
 */
int	builtin_cd(t_data *data, const char *path)
{
	int		ret;
	int		tab_len;
	int		i;

	ret = 0;
	if (!path)
		ret = handle_no_args(data);
	else if (ft_strncmp(path, "-", 2) == 0)
		ret = handle_minus(data);
	else if (chdir(path) == -1)
	{
		err_msg_cd(path, data);
		ret = -1;
	}
	if (ret != -1)
	{
		i = find_env_var("PWD=", data->env);
		tab_len = get_env_len(data->env);
		if (i != tab_len)
			handle_if_pwd(data);
		else if (i == tab_len)
			handle_no_pwd(data);
	}
	return (ret);
}
