/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:16:47 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/05 15:42:18 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	check_alpha_num(char c, va_list args, char *base, int fd)
{
	int	ret;

	ret = 0;
	if (c == 'c')
		ret = ft_putchar_fd_int(va_arg(args, int), fd);
	if (c == '%')
		ret = ft_putchar_fd_int(c, fd);
	if (c == 's')
		ret = ft_putstr_fd_int(va_arg(args, char *), fd);
	if (c == 'd' || c == 'i' || c == 'u')
	{
		if (c == 'd' || c == 'i')
			ret = ft_putnbr_b_fd_int(va_arg(args, int), base, fd);
		if (c == 'u')
			ret = ft_putnbr_b_fd_int(va_arg(args, unsigned int), base, fd);
	}
	if (ret < 0)
		return (-1);
	return (ret);
}

static int	check_hex(char c, va_list args, char *base, int fd)
{
	int	ret;

	ret = 0;
	if (c == 'x')
		ret = ft_putnbr_b_fd_int(va_arg(args, unsigned int), base, fd);
	if (c == 'X')
		ret = ft_putnbr_b_fd_int(va_arg(args, unsigned int), base, fd);
	if (ret < 0)
		return (-1);
	return (ret);
}

static int	check_ptr(va_list args, char *base, int fd)
{
	int				ret;
	int				tmp;
	unsigned long	nbr;

	ret = 0;
	nbr = va_arg(args, unsigned long);
	ret = ft_putstr_fd_int("0x", fd);
	if (ret < 0)
		return (-1);
	tmp = ft_putnbr_ptr(nbr, base, fd);
	if (tmp < 0)
		return (-1);
	ret += tmp;
	return (ret);
}

int	check_format(char c, va_list args, int fd)
{
	int		ret;
	char	*base_10;
	char	*hex_l;
	char	*hex_u;

	base_10 = "0123456789";
	hex_l = "0123456789abcdef";
	hex_u = "0123456789ABCDEF";
	ret = 0;
	if (c == 'c' || c == 's' || c == 'i' || c == 'd' || c == 'u' || c == '%')
		ret = check_alpha_num(c, args, base_10, fd);
	if (c == 'x')
		ret = check_hex(c, args, hex_l, fd);
	if (c == 'X')
		ret = check_hex(c, args, hex_u, fd);
	if (c == 'p')
		ret = check_ptr(args, hex_l, fd);
	if (ret < 0)
		return (-1);
	return (ret);
}
