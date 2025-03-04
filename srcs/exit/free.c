/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:47:06 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/27 13:34:33 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Free the data structure, close fds and exit
 *
 * @param data The data structure
 * @param err Int if there is an error or not
 */
void	free_before_exit(t_data *data)
{
	free_cmd_tree(data);
	free(data->cwd);
	close(data->fd_in);
	close(data->fd_out);
}

/**
 * @brief Free a tab of strings
 *
 * @param tab The tab to free
 * @param start The position to start freeing
 */
void	free_tab(char **tab, int start)
{
	if (tab)
	{
		while (tab[start])
			free_and_null(tab[start++]);
		free_and_null(tab);
	}
}

/**
 * @brief Free the entire command tree
 *
 * @param data The main data structure
 */
void	free_cmd_tree(t_data *data)
{
	if (data->cmd)
		free_from_cmd(data->cmd);
	data->cmd = NULL;
}

/**
 * @brief Free the data and set the pointer to NULL
 *
 * @param data The data to free
 */
void	free_and_null(void *data)
{
	if (data)
	{
		free(data);
		data = NULL;
	}
}
