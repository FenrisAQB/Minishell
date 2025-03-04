/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:39:36 by jbarbey           #+#    #+#             */
/*   Updated: 2025/01/28 21:28:09 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees an array from an index in the middle
 *
 * @param tab The array to free
 * @param i The index from where to free
 * @todo Needs to be moved in a free.c file
 */
void	free_mid_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free_and_null(tab[i]);
		i--;
	}
	free_and_null(tab);
}

/**
 * @brief Counts the amount of words present in the string
 *
 * @param s The string
 * @param start No space, The same as "s"
 * @return int Returns the amount of words counted
 */
static int	count_words(char *s, char *start)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		if (*s)
			count++;
		while (*s && *s != ' ')
		{
			if (*s == 34 || *s == 39)
				skip_quotes_ptr(&s);
			if (is_special_char(*s))
			{
				if (s - 1 >= start && *(s - 1) != ' ')
					count++;
				skip_spe_char(&s);
				break ;
			}
			s++;
		}
	}
	return (count);
}

/**
 * @brief Finds the start and end of a word
 *
 * @param s The pointer to the first character of the word, incremented to end
 * @param start The pointer which will be set to the start of the word
 */
static void	find_word(char **s, char **start)
{
	while (**s && **s == ' ')
		(*s)++;
	*start = *s;
	while (**s && **s != ' ')
	{
		if (**s == 34 || **s == 39)
			skip_quotes_ptr(s);
		if (is_special_char(**s))
		{
			if (*s == *start)
				skip_spe_char(s);
			return ;
		}
		(*s)++;
	}
}

/**
 * @brief Splits the string received from prompt and creates the command array
 *
 * @param s The string to split
 * @return char** The built command array
 */
char	**split(char *s)
{
	char	**ret;
	char	*start;
	int		i;

	ret = malloc(sizeof(char *) * (count_words(s, s) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (*s)
	{
		find_word(&s, &start);
		if (start < s)
		{
			ret[i] = malloc(sizeof(char) * (s - start + 1));
			if (!ret[i])
			{
				free_mid_tab(ret, i - 1);
				return (NULL);
			}
			ft_strlcpy(ret[i], start, s - start + 1);
			i++;
		}
	}
	ret[i] = NULL;
	return (ret);
}
