/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_lex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:33:53 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/26 17:38:59 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Exits the parsing and lexing functions
 *
 * @param data The main data structure
 * @param cmd_arr The command array
 * @param msg The error message
 * @param mode The mode to exit (exit or just error message)
 */
static void	exit_parsing(t_data *data, char **cmd_arr, char *msg, int mode)
{
	free_tab(cmd_arr, 0);
	if (mode == 0)
		error_message(msg, 2, 2);
	if (mode == 1)
		clean_exit(data, msg, 2, EXIT_FAILURE);
}

/**
 * @brief Checks the validity of command symbols (redirs and pipes)
 *
 * @param cmd_arr The command array
 * @return int Returns 0 on success and 1 on fail
 */
static int	check_spe_char(char **cmd_arr)
{
	int	i;
	int	token;

	i = 0;
	while (cmd_arr[i])
	{
		token = get_char_token(cmd_arr[i]);
		if (token == TOKEN_PIPE && i > 0 && get_char_token(cmd_arr[i - 1]))
			return (1);
		if (token == TOKEN_PIPE && cmd_arr[i][1])
			return (1);
		if (token == TOKEN_REDIR_SR && cmd_arr[i][1])
			return (1);
		if (token == TOKEN_REDIR_SL && cmd_arr[i][1])
			return (1);
		if (token == TOKEN_REDIR_DR && ft_strncmp(cmd_arr[i], ">>", 3))
			return (1);
		if (token == TOKEN_REDIR_DL && ft_strncmp(cmd_arr[i], "<<", 3))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Checks if env var assignements in relevant positions have valid names
 *
 * @param cmd_arr The command array
 * @return int Returns 0 on success and 1 on fail
 */
static int	check_env_var_assign(char **cmd_arr)
{
	int		i;
	char	*t;

	i = 0;
	while (cmd_arr[i])
	{
		t = ft_strchr(cmd_arr[i], '=');
		if (t && (i == 0 || get_char_token(cmd_arr[i - 1]) == TOKEN_PIPE))
		{
			if (ft_isdigit(cmd_arr[i][0]))
				return (1);
			if (t > cmd_arr[i] && *(t - 1) == '+')
				t--;
			t--;
			while (t >= cmd_arr[i])
			{
				if (!ft_isalnum(*t) && *t != '_')
					return (1);
				t--;
			}
		}
		i++;
	}
	return (0);
}

/**
 * @brief Some basic syntax checks
 *
 * @param cmd_arr The command array
 * @return int Returns 0 on success and 1 on fail
 */
static int	basic_cmd_sym_syntax(char **cmd_arr)
{
	int	i;
	int	token;
	int	tkn_nxt;

	i = 0;
	if (get_char_token(cmd_arr[0]) == TOKEN_PIPE)
		return (1);
	while (cmd_arr[i])
	{
		token = get_char_token(cmd_arr[i]);
		if (token && cmd_arr[i + 1])
		{
			tkn_nxt = get_char_token(cmd_arr[i + 1]);
			if (token == TOKEN_PIPE && tkn_nxt == TOKEN_PIPE)
				return (1);
			if (token != TOKEN_PIPE && tkn_nxt)
				return (1);
		}
		i++;
	}
	if (cmd_arr[i - 1] && get_char_token(cmd_arr[i - 1]))
		return (1);
	return (0);
}

/**
 * @brief The main function handling the parsing and lexing
 *
 * @param line The line read from prompt
 * @param data The main data structure
 * @return int Returns 0 on success and 1 on fail
 */
int	parse_and_lex(char **line, t_data *data)
{
	char	**cmd_arr;

	cmd_arr = split(*line);
	free(*line);
	if (!cmd_arr || !cmd_arr[0])
		return (error_message("Malloc: parse_and_lex:135", 2, EXIT_FAILURE), 1);
	if (check_spe_char(cmd_arr) || basic_cmd_sym_syntax(cmd_arr))
		return (exit_parsing(data, cmd_arr, "Syntax error", 0), 1);
	if (check_env_var_assign(cmd_arr))
		return (exit_parsing(data, cmd_arr, "Not a valid identifier", 0), 1);
	db_print_cmd_arr(cmd_arr, "Final command line array after parsing", BBLUE);
	if (lexer(cmd_arr, data))
		exit_parsing(data, cmd_arr, "Malloc: parse_and_lex:152", 1);
	free_tab(cmd_arr, 0);
	if (clean_tree(data, data->cmd))
		return (free_cmd_tree(data), 1);
	db_print_tree(data->cmd, "Final command line tree after lexing", BBLUE);
	return (0);
}
