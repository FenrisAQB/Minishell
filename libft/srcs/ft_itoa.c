/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:39:30 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/05 15:45:42 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	number_size(int n);

char	*ft_itoa(int n)
{
	char		*dest;
	long int	nb;
	int			size;

	nb = n;
	size = number_size(n);
	if (n < 0 || size == 0)
		size++;
	if (nb < 0)
		nb = -nb;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (0);
	dest[size] = '\0';
	while (size > 0)
	{
		size--;
		dest[size] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		dest[size] = 45;
	return (dest);
}

static int	number_size(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
