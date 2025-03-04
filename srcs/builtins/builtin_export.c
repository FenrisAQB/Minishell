/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:18:23 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/04 16:29:52 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Sort the environment array
 *
 * @param env The environment array
 * @return char** The sorted environment array
 */
static char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if ((ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0))
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

/**
 * @brief Duplicate the environment array without the _= variable
 *
 * @param data The main data structure
 * @param tmp_env The temporary environment array
 * @return char** The duplicated environment array
 */
static char	**dup_env_export(t_data *data, char **tmp_env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "_=", 2))
		{
			tmp_env[j] = ft_strdup(data->env[i]);
			if (!tmp_env[j])
			{
				while (j >= 0)
					free_and_null(tmp_env[j--]);
				free_and_null(tmp_env);
				clean_exit(data, "Malloc: builtin_export:70", 2, EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	tmp_env[j] = NULL;
	return (tmp_env);
}

/**
 * @brief The export builtin with no arguments
 * @details Print the environment array sorted
 * @param data The main data structure
 */
static void	export_no_args(t_data *data)
{
	int		i;
	char	**tmp_env;
	char	*equal;

	i = 0;
	tmp_env = ft_calloc(get_env_len(data->env) + 1, sizeof(char *));
	if (!tmp_env)
		clean_exit(data, "Malloc: builtin_export:94", 2, EXIT_FAILURE);
	tmp_env = dup_env_export(data, tmp_env);
	tmp_env = sort_env(tmp_env);
	while (tmp_env[i])
	{
		equal = ft_strchr(tmp_env[i], '=');
		if (equal)
		{
			*equal = '\0';
			printf("declare -x %s=\"%s\"\n", tmp_env[i], equal + 1);
			*equal = '=';
		}
		else
			printf("declare -x %s\n", tmp_env[i]);
		free(tmp_env[i]);
		i++;
	}
	free_and_null(tmp_env);
}

/**
 * @brief The export builtin
 *
 * @param data The main data structure
 * @param var The variable to export
 * @param content The content of the variable
 */
void	builtin_export(t_data *data, char *var, char *content)
{
	if (!var && !content)
		export_no_args(data);
	else
		update_env(var, content, data->env, data);
}
