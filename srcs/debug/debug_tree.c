/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:17:25 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/18 10:37:54 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Debug function to print a pipe node
 *
 * @param pipe The pointer to the pipe structure
 */
void	db_lst_print_pipe(t_pipe *pipe)
{
	if (DEBUG == 0)
		return ;
	printf("§--------PIPE node--------§\n");
	printf("type		:	{%s%d%s}\n", GREEN, pipe->type, RES);
	printf("left ptr	:	{%s%p%s}\n", GREEN, pipe->left, RES);
	if (pipe->left)
		printf("left type	:	{%s%d%s}\n", GREEN, pipe->left->type, RES);
	printf("right ptr	:	{%s%p%s}\n", GREEN, pipe->right, RES);
	if (pipe->right)
		printf("right type	:	{%s%d%s}\n", GREEN, pipe->right->type, RES);
	if (pipe->left)
		db_print_tree(pipe->left, NULL, NULL);
	if (pipe->right)
		db_print_tree(pipe->right, NULL, NULL);
}

/**
 * @brief Debug function to print a redir node
 *
 * @param redir The pointer to the redir structure
 */
void	db_lst_print_redir(t_redir *redir)
{
	if (DEBUG == 0)
		return ;
	printf("§--------REDIR node--------§\n");
	printf("type		:	{%s%d%s}\n", GREEN, redir->type, RES);
	printf("cmd ptr		:	{%s%p%s}\n", GREEN, redir->cmd, RES);
	if (redir->cmd)
		printf("cmd type	:	{%s%d%s}\n", GREEN, redir->cmd->type, RES);
	printf("file		:	{%s%s%s}\n", GREEN, redir->file, RES);
	printf("fd		:	{%s%d%s}\n", GREEN, redir->fd, RES);
	printf("in_out		:	{%s%d%s}\n", GREEN, redir->in_out, RES);
	if (redir->cmd)
		db_print_tree(redir->cmd, NULL, NULL);
}

/**
 * @brief Debug function to print an exec node
 *
 * @param exec The pointer to the exec structure
 */
void	db_lst_print_exec(t_exec *exec)
{
	int		i;
	char	*s;

	if (DEBUG == 0)
		return ;
	printf("§--------EXEC node--------§\n");
	printf("type		:	{%s%d%s}\n", GREEN, exec->type, RES);
	printf("full_cmd	:	{%s%s%s}\n", GREEN, exec->full_cmd, RES);
	printf("cmd tab		:	{%s%p%s}\n", GREEN, exec->cmd, RES);
	i = -1;
	while (exec->cmd[++i])
	{
		s = exec->cmd[i];
		printf("cmd [%s%d%s]\t\t:\t{%s%s%s}\n", BBLUE, i, RES, GREEN, s, RES);
	}
}

/**
 * @brief Debug function to print the command tree
 *
 * @param cmd The pointer to the first element of the tree
 * @param why Text to print before the tree for additional context. Or NULL
 * @param whyColor Defined color code to print the additional "why" in. Or NULL
 */
void	db_print_tree(t_cmd *cmd, char *why, char *whyColor)
{
	t_pipe	*pipe;
	t_redir	*redir;
	t_exec	*exec;

	if (DEBUG == 0)
		return ;
	if (why && whyColor)
		printf("\t%s%s%s\n", whyColor, why, RES);
	if (cmd->type == TOKEN_PIPE)
	{
		pipe = (t_pipe *) cmd;
		db_lst_print_pipe(pipe);
	}
	else if (cmd->type == TOKEN_REDIR)
	{
		redir = (t_redir *) cmd;
		db_lst_print_redir(redir);
	}
	else if (cmd->type == TOKEN_EXEC)
	{
		exec = (t_exec *) cmd;
		db_lst_print_exec(exec);
	}
}
