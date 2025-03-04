/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:17:43 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/23 16:29:44 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief The echo builtin
 * @details Print the given string to stdout
 * @param str The string to print
 * @param nl If true, print a newline at the end
 */
void	builtin_echo(char *str, int nl)
{
	if (str)
	{
		ft_putstr_fd(str, 1);
		if (nl)
			ft_putchar_fd('\n', 1);
	}
	else if (nl)
		ft_putchar_fd('\n', 1);
	free_and_null(str);
}
