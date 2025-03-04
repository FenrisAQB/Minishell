/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:24:52 by cdorig            #+#    #+#             */
/*   Updated: 2025/01/28 21:24:29 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Get the length of the environment array
 *
 * @param enp The environment array
 * @return i, the length of the array
 */
int	get_env_len(char **enp)
{
	int	i;

	i = 0;
	while (enp[i])
		i++;
	return (i);
}

/**
 * @brief Find the environment variable
 *
 * @param var The variable to find
 * @param enp The environment array
 * @return i The position of the variable
 */
int	find_env_var(const char *var, char **enp)
{
	int	i;

	i = 0;
	while (enp[i])
	{
		if (!ft_strncmp(enp[i], var, ft_strlen(var)))
			return (i);
		i++;
	}
	return (i);
}
