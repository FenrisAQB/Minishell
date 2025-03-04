/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:05:15 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/05 16:02:20 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	write_if_neg(long long nbr, char *base, int fd)
{
	int	ret;
	int	tmp;

	tmp = 0;
	ret = ft_putchar_fd_int('-', fd);
	if (ret < 0)
		return (-1);
	tmp = ft_putnbr_b_fd_int(-nbr, base, fd);
	if (tmp < 0)
		return (-1);
	else
		return (ret + tmp);
}

static int	write_num(long long nbr, char *base, int fd, int len)
{
	int	ret;
	int	tmp;

	ret = 0;
	if (nbr >= len)
	{
		tmp = ft_putnbr_b_fd_int(nbr / len, base, fd);
		if (tmp < 0)
			return (-1);
		ret += tmp;
		tmp = ft_putchar_fd_int(base[nbr % len], fd);
		if (tmp < 0)
			return (-1);
		ret += tmp;
	}
	if (nbr < len)
		ret = ft_putchar_fd_int(base[nbr % len], fd);
	if (ret < 0)
		return (-1);
	return (ret);
}

int	ft_putnbr_ptr(unsigned long nbr, char *base, int fd)
{
	size_t	len;
	int		ret;
	int		tmp;

	ret = 0;
	len = ft_strlen(base);
	if (len != 0)
	{
		if (nbr >= len)
		{
			tmp = ft_putnbr_ptr(nbr / len, base, fd);
			if (tmp < 0)
				return (-1);
			ret += tmp;
			tmp = ft_putchar_fd_int(base[nbr % len], fd);
			if (tmp < 0)
				return (-1);
			ret += tmp;
		}
	}
	if (nbr < len)
		ret = ft_putchar_fd_int(base[nbr % len], fd);
	if (ret < 0)
		return (-1);
	return (ret);
}

int	ft_putnbr_b_fd_int(long long nbr, char *base, int fd)
{
	int	len;
	int	ret;
	int	tmp;

	ret = 0;
	len = ft_strlen(base);
	if (len != 0)
	{
		if (nbr < 0)
		{
			ret = write_if_neg(nbr, base, fd);
			if (ret < 0)
				return (-1);
		}
		else
		{
			tmp = write_num(nbr, base, fd, len);
			if (tmp < 0)
				return (-1);
			ret += tmp;
		}
	}
	return (ret);
}
/*
#include <stdio.h>

static int	num_size(long long nbr, char *base)
{
	int	i;

	i = 0;
	if (nbr <= 0)
	{
		i++;
		nbr = -nbr;
	}
	while (nbr != 0)
	{
		nbr /= ft_strlen(base);
		i++;
	}
	return (i);
}

int	main(void)
{
	char		*base;
	int	test;
	int			res;

	test = -18446;
	base = "0123456789abcdef";
	printf("\nResult of putnbr_base is %d\n", ft_putnbr_ptr(test, base, 1));
	printf("num_length is %d\n", num_size(test, base));
	res = printf("%x", test);
	printf("\n");
	printf("Result of printf is %d\n", res);
	return (0);
}
*/
