/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_alpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:13:03 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/05 16:01:53 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putchar_fd_int(char c, int fd)
{
	return (write (fd, &c, 1));
}

int	ft_putstr_fd_int(char *s, int fd)
{
	if (!s)
	{
		if (ft_putstr_fd_int("(null)", fd) < 0)
			return (-1);
		return (6);
	}
	return (write(fd, s, ft_strlen(s)));
}
