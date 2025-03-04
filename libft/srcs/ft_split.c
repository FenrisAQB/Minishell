/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:53:33 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/05 15:53:09 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	words;

	if (!*str)
		return (0);
	i = 0;
	words = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c)
		{
			words++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (words);
}

static void	free_willy(char **dest, int i)
{
	if (!dest)
		return ;
	while (i >= 0)
	{
		free(dest[i]);
		i--;
	}
	free(dest);
}

static int	split_it(char **dest, const char *str, char c, int word)
{
	int	len;

	len = 0;
	if (!ft_strchr(str, c))
		len = ft_strlen(str);
	else
		len = ft_strchr(str, c) - str;
	dest[word] = ft_substr(str, 0, len);
	if (!dest[word])
		return (0);
	return (len);
}

char	**ft_split(const char *s, char c)
{
	int		len;
	int		word;
	char	**dest;

	dest = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!dest || !s)
		return (0);
	word = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			len = split_it(dest, s, c, word++);
			if (len == 0)
			{
				free_willy(dest, word - 1);
				return (0);
			}
			s += len;
		}
	}
	dest[word] = 0;
	return (dest);
}
