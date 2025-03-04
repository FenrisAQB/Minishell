/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:35:56 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/21 15:55:13 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees different pointers to return cleanly
 *
 * @param e The pointer to the exec structure
 * @param arr The pointer to the array
 * @param i The index from which to free the array
 */
static void	clean_exec_exit(t_exec *e, char **arr, int i)
{
	free_mid_tab(arr, i);
	free_and_null(e);
}

/**
 * @brief Starts building the exec structure
 *
 * @param cmd_arr The command array
 * @param end_i The index of the last valid word in the command array
 * @param st A pointer to the first valid word in the command array
 * @returns t_exec* The pointer to the exec node
 */
static t_exec	*lst_build_exec_2(char **cmd_arr, int end_i, int *st)
{
	t_exec	*e;
	int		r_count;
	int		size;

	*st = end_i;
	r_count = 0;
	while (*st >= 0 && get_char_token(cmd_arr[*st]) != TOKEN_PIPE)
	{
		if (cmd_arr[*st][0] == '<' || cmd_arr[*st][0] == '>')
			r_count++;
		(*st)--;
	}
	(*st)++;
	if (!init_exec(&e))
		return (NULL);
	size = end_i - (*st) + 1 - r_count * 2;
	e->cmd = malloc(sizeof(char *) * (size + 1));
	if (!e->cmd)
		return (free_and_null(e), NULL);
	e->cmd[size] = NULL;
	return (e);
}

/**
 * @brief Builds an exec node
 *
 * @param cmd_arr The command array
 * @param end_i The index of the last valid word in the command array
 * @returns t_cmd* The typecasted pointer to the exec node
 */
t_cmd	*lst_build_exec(char **cmd_arr, int end_i)
{
	t_exec	*e;
	int		start;
	int		j;

	e = lst_build_exec_2(cmd_arr, end_i, &start);
	if (!e)
		return (NULL);
	j = -1;
	while (cmd_arr[start] && start <= end_i)
	{
		if (get_char_token(cmd_arr[start]))
		{
			start += 2;
			continue ;
		}
		e->cmd[++j] = ft_strdup(cmd_arr[start++]);
		if (!e->cmd[j])
			return (clean_exec_exit(e, e->cmd, j - 1), NULL);
	}
	e->full_cmd = ft_strdup(e->cmd[0]);
	if (!e->full_cmd)
		return (clean_exec_exit(e, e->cmd, j), NULL);
	return ((t_cmd *)e);
}
