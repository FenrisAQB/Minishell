/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:54:16 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/03 22:29:14 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Duplicate the environment array
 *
 * @param data The main data structure
 * @param enp The environment array
 * @param tmp_env The temporary environment array
 */
static int	dup_env(t_data *data, char **enp, char **tmp_env)
{
	int	i;

	i = 0;
	while (enp[i])
	{
		tmp_env[i] = ft_strdup(enp[i]);
		if (!tmp_env[i])
		{
			while (i >= 0)
				free_and_null(tmp_env[i--]);
			free_and_null(tmp_env);
			return (0);
		}
		i++;
	}
	tmp_env[i] = NULL;
	free_tab(data->env, 0);
	data->env = tmp_env;
	return (1);
}

/**
 * @brief Create a new environment array
 *
 * @param data The main data structure
 * @param enp The environment array
 * @param new_entry The new entry to free in case of error
 */
static void	new_env(t_data *data, char **enp, char *new_entry)
{
	char	**tmp_env;
	int		tab_len;

	tab_len = get_env_len(enp);
	tmp_env = ft_calloc(tab_len + 1, sizeof(char *));
	if (!tmp_env || !dup_env(data, enp, tmp_env))
	{
		free_and_null(new_entry);
		clean_exit(data, "Malloc: handle_env:62", 2, EXIT_FAILURE);
	}
}

/**
 * @brief Add a new variable to the environment array
 *
 * @param data The main data structure
 * @param new_entry The new entry to add
 */
static void	add_var(t_data *data, char *new_entry)
{
	int		tab_len;
	char	**tmp_env;

	tab_len = get_env_len(data->env);
	tmp_env = ft_calloc(tab_len + 2, sizeof(char *));
	if (!tmp_env || !dup_env(data, data->env, tmp_env))
	{
		free_and_null(new_entry);
		clean_exit(data, "Malloc: handle_env:82", 2, EXIT_FAILURE);
	}
	tmp_env[tab_len] = new_entry;
	tmp_env[tab_len + 1] = NULL;
}

/**
 * @brief Update the environment array
 *
 * @param var The variable to update
 * @param content The content to update
 * @param enp The environment array
 * @param data The main data structure
 */
void	update_env(char *var, char *content, char **enp, t_data *data)
{
	int		i;
	int		tab_len;
	char	*new_entry;

	i = find_env_var(var, enp);
	tab_len = get_env_len(enp);
	new_entry = ft_strjoin(var, content);
	free_and_null(var);
	free_and_null(content);
	if (!new_entry)
		clean_exit(data, "Malloc: handle_env:108", 2, EXIT_FAILURE);
	if (!data->env)
		new_env(data, enp, new_entry);
	if (i != tab_len && data->env[i])
	{
		free_and_null(data->env[i]);
		data->env[i] = new_entry;
	}
	else if (i == tab_len)
		add_var(data, new_entry);
}
