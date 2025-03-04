/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:02:43 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/26 14:52:54 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Find the command in the PATH
 *
 * @param data The main data structure
 * @param e The execution node
 * @param paths The PATH array
 * @return char* The absolute path of the command
 */
char	*find_cmd(t_data *data, t_exec *e, char **paths)
{
	int		i;
	char	*tmp;

	i = -1;
	while (e->full_cmd[0] && paths && paths[++i])
	{
		tmp = ft_strjoin(paths[i], e->full_cmd);
		if (!tmp)
		{
			free_tab(paths, 0);
			clean_exit(data, "Malloc: cmd_utils:28", 2, EXIT_FAILURE);
		}
		if (!access(tmp, F_OK))
		{
			free_tab(paths, 0);
			return (tmp);
		}
		free(tmp);
	}
	free_tab(paths, 0);
	return (NULL);
}

/**
 * @brief Store input in a here document
 *
 * @param data The main data structure
 * @param r The redirection node
 */
void	store_in_here_doc(t_data *data, t_redir *r, char *q, int *fd)
{
	char	*line;

	if (dup2(data->fd_out, 1) < 0)
		clean_cmd_exit(data, fd[0], fd[1], "fd duplication");
	setup_signal(3);
	while (!g_here_doc_exit)
	{
		if (!g_here_doc_exit)
			line = readline("> ");
		if (!line)
			break ;
		if (*line && !ft_strncmp(line, r->file, ft_strlen(r->file) + 1))
		{
			free(line);
			break ;
		}
		if (!q)
			handle_dollar(&line, data->env);
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	close(fd[0]);
	close(fd[1]);
	clean_exit(data, 0, 0, g_here_doc_exit);
}

/**
 * @brief Fork a process to store input in a here document
 *
 * @param data The main data structure
 * @param r The redirection node
 * @param q The quote
 * @param fd The file descriptor tab
 * @return int The exit status
 */
int	fork_here_doc(t_data *data, t_redir *r, char *q, int *fd)
{
	int	hd_status;
	int	hd_pid;

	hd_pid = fork();
	if (hd_pid == 0)
		store_in_here_doc(data, r, q, fd);
	waitpid(hd_pid, &hd_status, 0);
	return (WEXITSTATUS(hd_status));
}
