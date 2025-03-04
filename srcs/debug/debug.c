/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:31:31 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/18 10:16:08 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Debug function to print the command array
 *
 * @param cmd The pointer to the command array
 * @param why Text to print before the tree for additional context. Or NULL
 * @param whyColor Defined color code to print the additional "why" in. Or NULL
 */
void	db_print_cmd_arr(char **cmd, char *why, char *whyColor)
{
	int	i;

	if (DEBUG == 0)
		return ;
	i = 0;
	if (why && whyColor)
		printf("\t%s%s%s\n", whyColor, why, RES);
	while (cmd[i])
	{
		printf("%s[%d] %s{%s}%s\n", BLUE, i, GREEN, cmd[i], RES);
		i++;
	}
}

/**
 * @brief Debug function to print any string
 *
 * @param s The pointer to the string
 * @param why Text to print before the tree for additional context. Or NULL
 * @param whyColor Defined color code to print the additional "why" in. Or NULL
 */
void	db_print_str(char *s, char *why, char *whyColor)
{
	if (DEBUG == 0)
		return ;
	if (why && whyColor)
		printf("\t%s%s%s ", whyColor, why, RES);
	printf("%s{%s}%s\n", GREEN, s, RES);
}

/**
 * @brief Debug function to print any number
 *
 * @param nbr The number
 * @param why Text to print before the tree for additional context. Or NULL
 * @param whyColor Defined color code to print the additional "why" in. Or NULL
 */
void	db_print_nbr(int nbr, char *why, char *whyColor)
{
	if (DEBUG == 0)
		return ;
	if (why && whyColor)
		printf("%s%s%s ", whyColor, why, RES);
	printf("%s{%d}%s\n", GREEN, nbr, RES);
}
