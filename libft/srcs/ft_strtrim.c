/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:43:40 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/26 14:06:07 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	is_set(const char *set, char c);
static char	*new_str(const char *s1, size_t start, size_t len);

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	while (is_set(set, s1[i]))
		i++;
	while (is_set(set, s1[j]))
		j--;
	return (new_str(s1, i, j - (i - 1)));
}

static int	is_set(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*new_str(const char *s1, size_t start, size_t len)
{
	size_t	i;
	char	*dest;
	size_t	s1_len;

	i = 0;
	s1_len = ft_strlen(s1);
	if (len <= 0 || start >= s1_len)
		return (ft_strdup(""));
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len && s1[i + start])
	{
		dest[i] = s1[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
