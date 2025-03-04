/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:48:12 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/26 14:31:02 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Initialize the main data structure
 *
 * @param data The main data structure
 */
void	init_data(t_data *data)
{
	data->env = NULL;
	data->cmd = NULL;
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		clean_exit(data, "Malloc: init_structs:27", 2, EXIT_FAILURE);
	data->is_pipe = 0;
	data->fd_out = dup(1);
	data->fd_in = dup(0);
}

/**
 * @brief Initialize the command structure
 *
 * @param cmd The command structure
 */
t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = 0;
	return (cmd);
}

/**
 * @brief Initialize and CALLOCS the pipe pointer
 *
 * @param pipe The pipe pointers adress
 */
int	init_pipe(t_pipe **pipe)
{
	*pipe = ft_calloc(1, sizeof(t_pipe));
	if (!*pipe)
		return (0);
	(*pipe)->type = TOKEN_PIPE;
	(*pipe)->left = NULL;
	(*pipe)->right = NULL;
	return (1);
}

/**
 * @brief Initialize and CALLOCS the exec pointer
 *
 * @param exec The exec pointers adress
 */
int	init_exec(t_exec **exec)
{
	*exec = ft_calloc(1, sizeof(t_exec));
	if (!*exec)
		return (0);
	(*exec)->type = TOKEN_EXEC;
	(*exec)->full_cmd = NULL;
	(*exec)->cmd = NULL;
	return (1);
}

/**
 * @brief Initialize and CALLOCS the redirection pointer
 *
 * @param redir The redirection pointers adress
 */
int	init_redir(t_redir **redir)
{
	*redir = ft_calloc(1, sizeof(t_redir));
	if (!*redir)
		return (0);
	(*redir)->type = TOKEN_REDIR;
	(*redir)->cmd = NULL;
	(*redir)->file = NULL;
	(*redir)->fd = -1;
	(*redir)->in_out = -1;
	return (1);
}
