/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:14:42 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/05 15:58:13 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*buff1;
	unsigned char	*buff2;

	i = 0;
	buff1 = (unsigned char *)s1;
	buff2 = (unsigned char *)s2;
	if (n < 1)
		return (0);
	while (buff1[i] && buff2[i] && buff1[i] == buff2[i] && i < n - 1)
		i++;
	if (buff1[i] == buff2[i])
		return (0);
	return (buff1[i] - buff2[i]);
}
