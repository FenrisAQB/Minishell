/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:02:42 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/07 09:49:48 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*add_to_stash(int fd, char *stash)
{
	char	*buff;
	int		bytes_read;

	buff = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash), free(buff), NULL);
		buff[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		stash = ft_strjoin_gnl(stash, buff);
		if (!stash)
			return (free(buff), NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (free(buff), stash);
}

static char	*extract_line(char *s)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	ret = ft_substr_gnl(s, 0, i + 1);
	return (ret);
}

static char	*clean_stash(char *s)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
		return (free(s), s = NULL, NULL);
	ret = ft_substr_gnl(s, i + 1, (ft_strlen(s) - i - 1));
	return (free(s), s = NULL, ret);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = add_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	ret = extract_line(stash[fd]);
	if (!ret)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	stash[fd] = clean_stash(stash[fd]);
	return (ret);
}
