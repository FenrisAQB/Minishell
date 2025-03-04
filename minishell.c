/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:18:32 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/27 11:21:36 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_here_doc_exit = 0;

/**
 * @brief Check if the line is empty
 *
 * @param line The line to check
 * @param mode 0 to check if the line is empty, 1 to free the line and check
 * @return int 1 if the line is empty, 0 otherwise
 */
static int	empty_line(char *line, int mode)
{
	char	*s;

	s = line;
	if (!*line && mode == 0)
		return (1);
	else if (!*line && mode == 1)
		return (free(line), 1);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (!*s && mode == 0)
		return (1);
	else if (!*s && mode == 1)
		return (free(line), 1);
	return (0);
}

/**
 * @brief Display the prompt and get the user input
 * @param line The user input
 */
void	display_prompt(char **line)
{
	setup_signal(0);
	g_here_doc_exit = 0;
	*line = readline(PROMPT);
	if (!*line)
		return ;
	if (!empty_line(*line, 0))
		add_history(*line);
	setup_signal(1);
}

/**
 * @brief Used to save or get the last command exit status
 *
 * @param new_code The last exit status or -1 to get without modifying
 * @return int Returns the saved exit status
 */
int	getset_exit_code(int new_code)
{
	static int	code;

	if (new_code >= 0)
		code = new_code;
	return (code);
}

/**
 * @brief The main loop running minishell
 *
 * @param data The main data structure
 */
static void	minishell_loop(t_data *data)
{
	char	*line;
	int		pid;
	int		status;

	while (1)
	{
		db_print_str("Enabled", "DEBUG mode", BGREEN);
		display_prompt(&line);
		if (!line)
			break ;
		if (empty_line(line, 1) || parse_and_lex(&line, data))
			continue ;
		if (is_only_builtin(data->cmd))
			run_no_pipe(data, data->cmd);
		else
		{
			pid = fork();
			if (pid == 0)
				run_cmd(data, data->cmd);
			waitpid(pid, &status, 0);
			getset_exit_code(WEXITSTATUS(status));
		}
		free_cmd_tree(data);
	}
}

/**
 * @brief Main function
 *
 * @param ac Number of arguments
 * @param av Arguments array
 * @param enp Environment array
 * @return int exit code
 */
int	main(int ac, char **av, char **enp)
{
	t_data	data;

	data = (t_data){};
	if (ac > 1)
		return (error_message("Too many arguments", 2, EXIT_FAILURE), 1);
	(void)av;
	init(enp, &data);
	minishell_loop(&data);
	clean_exit(&data, "exit", 1, getset_exit_code(-1) % 256);
}
