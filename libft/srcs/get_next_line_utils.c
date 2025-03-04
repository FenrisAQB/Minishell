/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:03:21 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/07 09:51:25 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr_gnl(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	if (!s || start >= ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ret = (char *)ft_calloc((len + 1), sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		ret[i] = s[i + start];
		i++;
	}
	return (ret);
}

char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = (char *)ft_calloc(1, sizeof(char));
		if (!s1)
			return (NULL);
	}
	ret = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!ret)
		return (free(s1), NULL);
	while (s1[j])
		ret[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	free(s1);
	return (ret);
}
