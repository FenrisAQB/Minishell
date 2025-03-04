/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:35:58 by jbarbey           #+#    #+#             */
/*   Updated: 2025/01/28 20:59:40 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees different pointers to return cleanly
 *
 * @param l The left part of the pipe
 * @param r The right part of the pipe
 */
static void	clean_pipe_exit(t_cmd *l, t_cmd *r)
{
	if (l)
		free_from_cmd(l);
	if (r)
		free_from_cmd(r);
}

/**
 * @brief Builds the left part of the pipe
 *
 * @param cmd_arr The command array
 * @param pipe_i The index of the pipe in the command array
 * @return t_cmd* The pointer to store in the left side of the pipe
 */
static t_cmd	*lst_build_left_pipe(char **cmd_arr, int pipe_i)
{
	int		i;
	int		r_count;
	t_cmd	*c;

	i = pipe_i - 1;
	r_count = 0;
	c = NULL;
	while (i >= 0 && cmd_arr[i][0] != '|')
	{
		if (get_char_token(cmd_arr[i]) > 7 && get_char_token(cmd_arr[i]) < 12)
			r_count++;
		i--;
	}
	if (r_count)
		c = lst_build_from_redir(cmd_arr, pipe_i - 1, r_count);
	else
		c = lst_build_exec(cmd_arr, pipe_i - 1);
	if (!c)
		return (NULL);
	return (c);
}

/**
 * @brief Builds the right part of the pipe
 *
 * @param cmd_arr The command array
 * @param pipe_i The index of the pipe in the command array
 * @return t_cmd* The pointer to store in the right side of the pipe
 */
static t_cmd	*lst_build_right_pipe(char **cmd_arr, int pipe_i)
{
	int		i;
	int		r_count;
	t_cmd	*c;

	i = pipe_i + 1;
	r_count = 0;
	c = NULL;
	while (cmd_arr[i])
	{
		if (cmd_arr[i][0] == '|')
		{
			c = lst_build_from_pipe(cmd_arr, i);
			break ;
		}
		if (get_char_token(cmd_arr[i]) > 7 && get_char_token(cmd_arr[i]) < 12)
			r_count++;
		i++;
	}
	if (r_count && !c)
		c = lst_build_from_redir(cmd_arr, i - 1, r_count);
	else if (!c)
		c = lst_build_exec(cmd_arr, i - 1);
	if (!c)
		return (NULL);
	return (c);
}

/**
 * @brief Builds a pipe node
 *
 * @param cmd_arr The command array
 * @param pipe_i The index of the pipe in the command array
 * @return t_cmd* The typecasted pointer to the pipe node
 */
t_cmd	*lst_build_from_pipe(char **cmd_arr, int pipe_i)
{
	t_pipe	*p;
	t_cmd	*left;
	t_cmd	*right;

	left = lst_build_left_pipe(cmd_arr, pipe_i);
	if (!left)
		return (NULL);
	right = lst_build_right_pipe(cmd_arr, pipe_i);
	if (!right)
		return (clean_pipe_exit(left, NULL), NULL);
	if (!init_pipe(&p))
		return (clean_pipe_exit(left, right), NULL);
	p->left = left;
	p->right = right;
	return ((t_cmd *)p);
}
