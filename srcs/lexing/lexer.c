/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:47:53 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/22 12:01:38 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Removes highest level of single or double quotes in string
 *
 * @param word The string to remove quotes from
 * @param t Same input as word
 */
void	remove_quotes(char *word, char *t)
{
	char	*q;
	char	quote_val;

	while (*t)
	{
		if (*t == '\'' || *t == '\"')
		{
			quote_val = *t;
			q = ft_strchr(t + 1, quote_val);
			if (q)
			{
				*t = '\0';
				*q = '\0';
				ft_strlcat(word, t + 1, ft_strlen(word) + ft_strlen(t + 1) + 1);
				ft_strlcat(word, q + 1, ft_strlen(word) + ft_strlen(q + 1) + 1);
				t = q - 2;
			}
			t++;
		}
		else
			t++;
	}
}

/**
 * @brief Lexer starting to build the command tree
 *
 * @param cmd_arr The command array
 * @param data The main data structure to store the first node of the tree
 * @return int Returns 0 on success and 1 on fail
 */
int	lexer(char **cmd_arr, t_data *data)
{
	int	i;
	int	r_count;

	i = 0;
	r_count = 0;
	data->is_pipe = 0;
	while (cmd_arr[i])
	{
		if (cmd_arr[i][0] == '|')
		{
			data->cmd = lst_build_from_pipe(cmd_arr, i);
			data->is_pipe = 1;
			break ;
		}
		if (get_char_token(cmd_arr[i]) > 7 && get_char_token(cmd_arr[i]) < 12)
			r_count++;
		i++;
	}
	if (r_count && !data->cmd)
		data->cmd = lst_build_from_redir(cmd_arr, i - 1, r_count);
	else if (!data->cmd)
		data->cmd = lst_build_exec(cmd_arr, i - 1);
	if (!data->cmd)
		return (1);
	return (0);
}
