/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:10:03 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/26 18:58:29 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Clean the exec node of quotes and handle dollar
 *
 * @param data The main data structure
 * @param e The exec node
 */
static void	clean_exec(t_data *data, t_exec *e)
{
	int	i;

	i = 0;
	if (e->full_cmd)
	{
		if (handle_dollar(&e->full_cmd, data->env))
			clean_exit(data, "Malloc: clean_tree:24", 2, EXIT_FAILURE);
		remove_quotes(e->full_cmd, e->full_cmd);
	}
	while (e->cmd[i])
	{
		if (handle_dollar(&e->cmd[i], data->env))
			clean_exit(data, "Malloc: clean_tree:30", 2, EXIT_FAILURE);
		remove_quotes(e->cmd[i], e->cmd[i]);
		i++;
	}
}

/**
 * @brief Store here_doc content in pipe fd
 * 
 * @param data The main data structure
 * @param r The redir node
 */
static int	store_doc(t_data *data, t_redir *r)
{
	int		fd[2];
	char	*q;

	pipe(fd);
	q = ft_strchr(r->file, '\'');
	if (!q)
		q = ft_strchr(r->file, '\"');
	remove_quotes(r->file, r->file);
	if (fork_here_doc(data, r, q, fd))
		return (close(fd[0]), close(fd[1]), 1);
	r->fd = fd[0];
	close(fd[1]);
	return (0);
}

/**
 * @brief Clean the redir node of quotes and handle dollar
 *
 * @param data The main data structure
 * @param r The redir node
 */
static int	clean_redir(t_data *data, t_redir *r)
{
	if (r->file && r->in_out != TOKEN_REDIR_DL)
	{
		if (handle_dollar(&r->file, data->env))
			clean_exit(data, "Malloc: clean_tree:41", 2, EXIT_FAILURE);
		remove_quotes(r->file, r->file);
	}
	if (r->file && r->in_out == TOKEN_REDIR_DL)
	{
		if (store_doc(data, r))
			return (1);
	}
	if (clean_tree(data, r->cmd))
		return (1);
	return (0);
}

/**
 * @brief Clean the tree of quotes and handle dollar
 *
 * @param data The main data structure
 * @param cmd The command tree
 */
int	clean_tree(t_data *data, t_cmd *cmd)
{
	t_pipe	*p;

	if (!cmd)
		return (0);
	if (cmd->type == TOKEN_PIPE)
	{
		p = (t_pipe *) cmd;
		if (clean_tree(data, p->left) || clean_tree(data, p->right))
			return (1);
	}
	else if (cmd->type == TOKEN_REDIR)
	{
		if (clean_redir(data, (t_redir *) cmd))
			return (1);
	}
	else if (cmd->type == TOKEN_EXEC)
		clean_exec(data, (t_exec *) cmd);
	return (0);
}
