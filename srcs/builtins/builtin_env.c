/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:52:21 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/18 10:02:38 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Print the environment variables
 *
 * @param data The main data structure
 */
void	builtin_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			ft_putendl_fd(data->env[i], 1);
		i++;
	}
}
