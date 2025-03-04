/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:11:33 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/27 14:32:13 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if the string is a valid exit code
 *
 * @param str The string to check
 * @return int The index of the first invalid character
 */
static int	check_code(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == 9 || str[i] == 10 || str[i] == 11
		|| str[i] == 12 || str[i] == 13 || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] == 9 || str[i] == 10 || str[i] == 11
		|| str[i] == 12 || str[i] == 13 || str[i] == 32)
		i++;
	return (i);
}

/**
 * @brief Convert a string to a long long int
 *
 * @param data The main data structure
 * @param str The string to convert
 * @return long long int The converted string
 */
static long long int	ft_atol(t_data *data, const char *str)
{
	long long	nb;
	int			i;
	int			neg;

	nb = 0;
	neg = 1;
	i = 0;
	while (str[i] == 9 || str[i] == 10 || str[i] == 11
		|| str[i] == 12 || str[i] == 13 || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (str[i] && str[i] > 47 && str[i] < 58)
	{
		if (neg > 0 && (nb > LMAX / 10 || (nb == LMAX / 10 && str[i] - 48 > 7)))
			clean_exit(data, "exit: numeric argument required", 2, 2);
		if (neg < 0 && (nb < LMIN / 10 || (nb == LMIN / 10 && str[i] - 48 > 8)))
			clean_exit(data, "exit: numeric argument required", 2, 2);
		nb = (nb * 10) + neg * (str[i++] - 48);
	}
	return (nb);
}

/**
 * @brief Exit the minishell
 *
 * @param data The main data structure
 * @param e The execution node
 */
void	builtin_exit(t_data *data, t_exec *e)
{
	int			i;
	long long	code;

	i = 0;
	code = 0;
	if (e->cmd[1])
	{
		code = ft_atol(data, e->cmd[1]);
		if (ft_strlen(e->cmd[1]) == 0)
			clean_exit(data, "exit: numeric argument required", 2, 2);
		i = check_code(e->cmd[1]);
		if (e->cmd[1][i])
			clean_exit(data, "exit: numeric argument required", 2, 2);
	}
	if (e->cmd[1] && e->cmd[2])
	{
		error_message("exit: too many arguments", 2, EXIT_FAILURE);
		return ;
	}
	clean_exit(data, "exit", 1, code);
}
