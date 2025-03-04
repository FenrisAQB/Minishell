/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:12:33 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/26 10:59:59 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handle the shell level
 * @param data The main data structure
 * @param var The environment variable
 * @return char* The new shell level
 */
static char	*handle_shlvl(char *var)
{
	char	*tmp;
	int		lvl;

	tmp = ft_strtrim(var, "SHLVL=");
	if (!tmp)
		return (NULL);
	lvl = ft_atoi(tmp);
	free_and_null(tmp);
	lvl++;
	tmp = ft_itoa(lvl);
	if (!tmp)
		return (NULL);
	return (tmp);
}

/**
 * @brief Handle copy of the environment array
 * @details Modify the shell level and copy the environment array
 * @param enp The environment array
 * @param data The main data structure
 */
static void	init_env(char **enp, t_data *data)
{
	char	*tmp;
	int		i;
	int		tab_len;
	char	*var;

	var = ft_strdup("SHLVL=");
	if (!var)
		clean_exit(data, "Malloc: init:53", 2, EXIT_FAILURE);
	i = find_env_var(var, enp);
	tab_len = get_env_len(enp);
	if (i != tab_len)
		tmp = handle_shlvl(enp[i]);
	else
		tmp = ft_strdup("1");
	if (!tmp)
	{
		free_and_null(var);
		clean_exit(data, "Malloc: init:63", 2, 1);
	}
	update_env(var, tmp, enp, data);
}

/**
 * @brief Initialize the environment and paths
 *
 * @param enp The environment array
 * @param data The main data structure
 */
void	init(char **enp, t_data *data)
{
	init_data(data);
	data->cmd = NULL;
	init_env(enp, data);
}
