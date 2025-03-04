/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:01:28 by cdorig            #+#    #+#             */
/*   Updated: 2025/01/28 09:52:24 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Reassign the environment array after unsetting a variable
 *
 * @param data The main data structure
 * @param i The index of the variable that was unset
 */
static void	reassign_env(t_data *data, int i)
{
	while (data->env[i + 1])
	{
		data->env[i] = data->env[i + 1];
		i++;
	}
	data->env[i] = NULL;
}

/**
 * @brief Unset an environment variable
 * @param data The main data structure
 * @param var The variable to unset
 */
void	builtin_unset(t_data *data, const char *var)
{
	int		i;
	int		tab_len;
	char	*tmp;

	tab_len = get_env_len(data->env);
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		clean_exit(data, "Malloc: builtin_unset:45", 2, 1);
	i = find_env_var(tmp, data->env);
	if (i == tab_len)
	{
		free_and_null(tmp);
		return ;
	}
	if (!ft_strncmp(tmp, "PWD=", 4))
	{
		free_and_null(data->cwd);
		data->cwd = NULL;
	}
	free_and_null(tmp);
	free_and_null(data->env[i]);
	reassign_env(data, i);
}
