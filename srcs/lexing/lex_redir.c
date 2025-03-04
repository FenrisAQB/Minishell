/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:35:57 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/21 15:55:24 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Builds a redir node with no exec
 *
 * @param cmd_arr The command array
 * @param end_i The index of the last valid word in the command array
 * @return t_cmd* The typecasted pointer to the redir node
 */
static t_cmd	*lst_redir_ne(char **cmd_arr, int end_i)
{
	t_redir	*r;
	int		token;

	if (!init_redir(&r))
		return (NULL);
	token = 0;
	while (end_i >= 0 && token != TOKEN_PIPE)
	{
		token = get_char_token(cmd_arr[end_i]);
		if (token > 7 && token < 12)
			break ;
		end_i--;
	}
	r->file = ft_strdup(cmd_arr[end_i + 1]);
	if (!r->file)
		return (free_from_cmd((t_cmd *)r), NULL);
	r->in_out = token;
	return ((t_cmd *)r);
}

/**
 * @brief Builds a redir node with an exec
 *
 * @param cmd_arr The command array
 * @param end_i The index of the last valid word in the command array
 * @return t_cmd* The typecasted pointer to the redir node
 */
static t_cmd	*lst_redir_we(char **cmd_arr, int end_i)
{
	t_redir	*r;
	t_cmd	*c;
	int		token;

	c = lst_build_exec(cmd_arr, end_i);
	if (!c)
		return (NULL);
	if (!init_redir(&r))
		return (free_from_cmd(c), NULL);
	r->cmd = c;
	token = 0;
	while (end_i >= 0 && token != TOKEN_PIPE)
	{
		token = get_char_token(cmd_arr[end_i]);
		if (token > 7 && token < 12)
			break ;
		end_i--;
	}
	r->file = ft_strdup(cmd_arr[end_i + 1]);
	if (!r->file)
		return (free_from_cmd((t_cmd *)r), NULL);
	r->in_out = token;
	return ((t_cmd *)r);
}

/**
 * @brief Decides wheter to build a redir with or without exec
 *
 * @param cmd_arr The command array
 * @param end_i The index of the last valid word in the command array
 * @return t_cmd* The typecasted pointer to the redir node
 */
static t_cmd	*lst_circulation_officer(char **cmd_arr, int end_i)
{
	int	i;
	int	cnt;

	i = end_i;
	cnt = 0;
	while (i >= 0 && cmd_arr[i][0] != '|')
	{
		if (get_char_token(cmd_arr[i]) > 7 && get_char_token(cmd_arr[i]) < 12)
			cnt++;
		i--;
	}
	i++;
	if (end_i - i - cnt * 2 < 0)
		return (lst_redir_ne(cmd_arr, end_i));
	return (lst_redir_we(cmd_arr, end_i));
}

/**
 * @brief Builds a redir node containing another redir node
 *
 * @param cmd_arr The command array
 * @param cnt The number of redirs left to handle
 * @param token No space, set to 0
 * @return t_cmd* The typecasted pointer to the redir node
 */
static t_cmd	*lst_mult_redir(char **cmd_arr, int end_i, int cnt, int token)
{
	t_redir	*r;
	t_cmd	*c;

	if (cnt >= 3)
		c = lst_mult_redir(cmd_arr, end_i, cnt - 1, 0);
	else
		c = lst_circulation_officer(cmd_arr, end_i);
	if (!c)
		return (NULL);
	if (!init_redir(&r))
		return (free_from_cmd(c), NULL);
	r->cmd = c;
	while (end_i >= 0 && token != TOKEN_PIPE && cnt >= 1)
	{
		token = get_char_token(cmd_arr[end_i]);
		if (token > 7 && token < 12)
			cnt--;
		end_i--;
	}
	r->file = ft_strdup(cmd_arr[end_i + 2]);
	if (!r->file)
		return (free_from_cmd((t_cmd *)r), NULL);
	r->in_out = token;
	return ((t_cmd *)r);
}

/**
 * @brief Builds a redir node
 *
 * @param cmd_arr The command array
 * @param end_i The index of the last valid word in the command array
 * @param cnt The number of redirs to handle
 * @return t_cmd* The typecasted pointer to the redir node
 */
t_cmd	*lst_build_from_redir(char **cmd_arr, int end_i, int cnt)
{
	int	st;

	st = end_i;
	while (st >= 0 && get_char_token(cmd_arr[st]) != TOKEN_PIPE)
		st--;
	st++;
	if (cnt >= 2)
		return (lst_mult_redir(cmd_arr, end_i, cnt, 0));
	if (end_i - st - cnt * 2 < 0)
		return (lst_redir_ne(cmd_arr, end_i));
	return (lst_redir_we(cmd_arr, end_i));
}
