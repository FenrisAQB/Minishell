/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:08:43 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/26 10:42:11 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Run the left side of the pipe
 * @details Duplicate the write end of the pipe to stdout and close the read end
 * @param data The main data structure
 * @param p The pipe node
 * @param p_fd The pipe file descriptors
 */
static void	pipe_left(t_data *data, t_pipe *p, int *p_fd)
{
	db_print_str("pipe_left", "In", BBLUE);
	if (dup2(p_fd[1], 1) < 0)
		clean_cmd_exit(data, p_fd[0], p_fd[1], "fd duplication");
	if (close(p_fd[0]) < 0)
		clean_cmd_exit(data, -1, p_fd[1], "write pipe fd closing");
	if (close(p_fd[1]) < 0)
		clean_exit(data, "read pipe fd closing", 2, 9);
	run_cmd(data, p->left);
}

/**
 * @brief Run the right side of the pipe
 * @details Duplicate the read end of the pipe to stdin and close the write end
 * @param data The main data structure
 * @param p The pipe node
 * @param p_fd The pipe file descriptors
 */
static void	pipe_right(t_data *data, t_pipe *p, int *p_fd)
{
	db_print_str("pipe_right", "In", BBLUE);
	if (dup2(p_fd[0], 0) < 0)
		clean_cmd_exit(data, p_fd[0], p_fd[1], "fd duplication");
	if (close(p_fd[1]) < 0)
		clean_cmd_exit(data, p_fd[0], -1, "read pipe fd closing");
	if (close(p_fd[0]) < 0)
		clean_exit(data, "write pipe fd closing", 2, 9);
	run_cmd(data, p->right);
}

/**
 * @brief Run the pipe command
 * @details Create a pipe, fork, run the left side of the pipe, then the right
 * @param data The main data structure
 * @param p The pipe node
 */
void	pipe_cmd(t_data *data, t_pipe *p)
{
	int	p_fd[2];
	int	pid_r;
	int	pid_l;
	int	status;

	db_print_str("pipe_cmd", "In", BBLUE);
	db_print_tree((t_cmd *)p, 0, 0);
	if (pipe(p_fd) < 0)
		clean_exit(data, "Pipe error", 2, 32);
	pid_l = fork();
	if (pid_l == 0)
		pipe_left(data, p, p_fd);
	pid_r = fork();
	if (pid_r == 0)
		pipe_right(data, p, p_fd);
	if (close(p_fd[1]) < 0)
		clean_cmd_exit(data, p_fd[0], -1, "read pipe fd closing");
	if (close(p_fd[0]) < 0)
		clean_exit(data, "write pipe fd closing", 2, 9);
	waitpid(pid_l, 0, 0);
	waitpid(pid_r, &status, 0);
	clean_exit(data, 0, 0, WEXITSTATUS(status));
}
