/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:39:21 by jbarbey           #+#    #+#             */
/*   Updated: 2025/01/28 21:20:00 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Skips closed quotes in a string
 *
 * @param s The pointer to the starting quote
 */
void	skip_quotes_ptr(char **s)
{
	char	*t;
	char	quote;

	t = *s;
	quote = *t;
	t++;
	while (*t && *t != quote)
		t++;
	if (*t == quote)
		*s = t;
}

/**
 * @brief Checks if the character is a pipe or redir
 *
 * @param c The character to check
 * @return int Returns 2 for a pipe, 1 for a redir and 0 if none
 */
int	is_special_char(char c)
{
	if (c == '<' || c == '>')
		return (1);
	if (c == '|')
		return (2);
	return (0);
}

/**
 * @brief Skips the pipe or redir
 *
 * @param s The pointer to the first character
 */
void	skip_spe_char(char **s)
{
	if (is_special_char(**s) == 2)
	{
		(*s)++;
		return ;
	}
	while (**s && is_special_char(**s))
		(*s)++;
}

/**
 * @brief Checks if current character is in single quotes
 *
 * @param s The pointer to the start of the string
 * @param t The pointer to the character to check
 * @return int Return 1 if it is contained and 0 if not
 */
int	is_in_single_quotes(char *s, char *t)
{
	char	*first_quote;
	char	quote;

	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			quote = *s;
			first_quote = s;
			s++;
			while (*s && *s != quote)
				s++;
			if (*s != quote)
				s = first_quote;
			if (t > first_quote && t < s && quote == '\'')
				return (1);
		}
		s++;
	}
	return (0);
}

/**
 * @brief Get the right pipe or redir TOKEN
 *
 * @param c The pointer to the character to evaluate
 * @return int Returns the corresponding token or 0 if none
 */
int	get_char_token(char *c)
{
	if (*c == '|')
		return (TOKEN_PIPE);
	if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (TOKEN_REDIR_DL);
		return (TOKEN_REDIR_SL);
	}
	if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (TOKEN_REDIR_DR);
		return (TOKEN_REDIR_SR);
	}
	return (0);
}
