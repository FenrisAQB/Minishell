/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:51 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/27 14:02:43 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Print an error message to the specified fd and set err code
 *
 * @param msg The error message
 * @param fd The file descriptor on which to write
 * @param code The exit code
 */
void	error_message(char *msg, int fd, int code)
{
	if (fd == 2)
	{
		ft_putstr_fd(RED, fd);
		ft_putstr_fd("Minishell: Error: ", fd);
	}
	ft_putendl_fd(msg, fd);
	ft_putstr_fd(RES, fd);
	getset_exit_code(code);
}

/**
 * @brief Exit the program cleanly
 * @details If msg, print it, free everything and exit with err code
 * @param data The main data structure
 * @param msg The error message
 * @param fd The file descriptor on which to write
 * @param code The exit code
 */
void	clean_exit(t_data *data, char *msg, int fd, int code)
{
	if (msg)
		error_message(msg, fd, code);
	if (data)
	{
		free_tab(data->env, 0);
		free_and_null(data->cwd);
		free_cmd_tree(data);
		close(data->fd_in);
		close(data->fd_out);
	}
	exit(code);
}

/**
 * @brief Print cd-specific error message
 *
 * @param path the path that was not found
 * @param data the main data structure
 */
void	err_msg_cd(const char *path, t_data *data)
{
	char	*msg;
	char	*tmp;

	tmp = ft_strjoin("cd: ", path);
	if (!tmp)
		clean_exit(data, "Malloc: exit:66", 2, EXIT_FAILURE);
	msg = ft_strjoin(tmp, ": No such file or directory");
	free_and_null(tmp);
	if (!msg)
		clean_exit(data, "Malloc: exit:70", 2, EXIT_FAILURE);
	error_message(msg, 2, EXIT_FAILURE);
	free_and_null(msg);
}

/**
 * @brief Exit the program cleanly after a command
 *
 * @param data The main data structure
 * @param fdi The input file descriptor
 * @param fdo The output file descriptor
 * @param msg The error message
 */
void	clean_cmd_exit(t_data *data, int fdi, int fdo, char *msg)
{
	if (fdi != -1)
		close(fdi);
	if (fdo != -1)
		close(fdo);
	clean_exit(data, msg, 2, 9);
}
