/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:47:26 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/05 15:51:14 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	iter(const char *str, va_list args, int *i)
{
	int	tmp;
	int	ret;
	int	fd;

	fd = 1;
	ret = 0;
	if (str[*i] == '%')
	{
		*i += 1;
		tmp = check_format(str[*i], args, fd);
		if (tmp < 0)
			return (-1);
		ret += tmp;
	}
	else
	{
		if (ft_putchar_fd_int(str[*i], fd) < 0)
			return (-1);
		ret++;
	}
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	int		ret;
	int		i;
	int		tmp;
	va_list	args;

	va_start(args, str);
	ret = 0;
	i = 0;
	while (str[i])
	{
		tmp = iter(str, args, &i);
		if (tmp < 0)
		{
			va_end(args);
			return (-1);
		}
		ret += tmp;
		i++;
	}
	va_end(args);
	return (ret);
}
