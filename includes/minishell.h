/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:06:10 by jbarbey           #+#    #+#             */
/*   Updated: 2025/02/27 14:34:14 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <limits.h>
# include "../libft/includes/libft.h"

/* Defines */

# define DEBUG 0

# define RES "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BGREEN "\033[1;32m"
# define BLUE "\033[0;34m"
# define BBLUE "\033[1;34m"

# define PROMPT "\033[0;34mMinishell>\033[0m"

# define LMAX LLONG_MAX
# define LMIN LLONG_MIN

/* Global variable */
extern int	g_here_doc_exit;

/* Enum structures */

typedef enum e_token
{
	TOKEN_PIPE				= 1,
	TOKEN_REDIR_SR			= 8,
	TOKEN_REDIR_SL			= 9,
	TOKEN_REDIR_DR			= 10,
	TOKEN_REDIR_DL			= 11,
	TOKEN_ECHO				= 15,
	TOKEN_CD				= 16,
	TOKEN_PWD				= 17,
	TOKEN_EXPORT			= 18,
	TOKEN_UNSET				= 19,
	TOKEN_ENV				= 20,
	TOKEN_EXIT				= 21,
	TOKEN_VAR				= 22,
	TOKEN_REDIR				= 23,
	TOKEN_EXEC				= 24,
}	t_token;

/* Structures */

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		fd;
	int		in_out;
}	t_redir;

typedef struct s_exec
{
	int		type;
	char	*full_cmd;
	char	**cmd;
}	t_exec;

typedef struct s_data
{
	char	**env;
	t_cmd	*cmd;
	char	*cwd;
	int		is_pipe;
	int		fd_out;
	int		fd_in;
}	t_data;

/* Functions */

// readline.h
char	*readline(const char *prompt);

// builtins
	// builtin_cd.c
int		builtin_cd(t_data *data, const char *path);
	// builtin_echo.c
void	builtin_echo(char *str, int nl);
	// builtin_env.c
void	builtin_env(t_data *data);
	// builtin_exit.c
void	builtin_exit(t_data *data, t_exec *e);
	// builtin_export.c
void	builtin_export(t_data *data, char *var, char *content);
	// builtin_pwd.c
void	builtin_pwd(t_data *data);
	// builtin_unset.c
void	builtin_unset(t_data *data, const char *var);

// debug
	// debug.c
void	db_print_cmd_arr(char **cmd, char *why, char *whyColor);
void	db_print_str(char *s, char *why, char *whyColor);
void	db_print_nbr(int nbr, char *why, char *whyColor);
	// debug_tree.c
void	db_lst_print_pipe(t_pipe *pipe);
void	db_lst_print_redir(t_redir *redir);
void	db_lst_print_exec(t_exec *exec);
void	db_print_tree(t_cmd *cmd, char *why, char *whyColor);

// env
	// env_utils.c
int		get_env_len(char **enp);
int		find_env_var(const char *var, char **enp);
	// handle_env.c
void	update_env(char *var, char *content, char **enp, t_data *data);

// exec
	// cmd_utils.c
char	*find_cmd(t_data *data, t_exec *e, char **paths);
int		fork_here_doc(t_data *data, t_redir *r, char *q, int *fd);
void	store_in_here_doc(t_data *data, t_redir *r, char *q, int *fd);
	// exec_cmd.c
void	exec_cmd(t_data *data, t_exec *e, char *abs_cmd, char **argv);
	// parse_tree.c
int		last_redir_of_kind(t_redir *redir, int token);
int		exec_in_branch(t_redir *redir);
int		is_only_builtin(t_cmd *cmd);
	// pipe_cmd.c
void	pipe_cmd(t_data *data, t_pipe *p);
	// redir_cmd.c
void	redir_cmd(t_data *data, t_redir *r);
	// redir_for_builtin.c
void	redir_cmd_for_builtin(t_data *data, t_redir *r);
	// run_builtin.c
int		is_builtin(t_exec *e);
void	run_builtin(t_data *data, t_exec *e);
void	run_no_pipe(t_data *data, t_cmd *cmd);
	// run_cd.c
void	run_cd(t_data *data, t_exec *e);
	// run_cmd.c
void	run_cmd(t_data *data, t_cmd *cmd);
	// run_unset.c
void	run_unset(t_data *data, t_exec *e);
	// run_echo.c
void	run_echo(t_data *data, t_exec *e);
	// run_env.c
void	run_env(t_data *data, t_exec *e);
	// run_export.c
void	run_export(t_data *data, t_exec *e);
	// run_var.c
void	run_var(t_data *data, t_exec *e, int i);
	// var_utils.c
char	*extract_var(char *str, t_data *data);
char	*extract_content(char *str, char *var, t_data *data);
char	*trim_plus(char *var, char *content, t_data *data);
char	*join_content(char *var, char *content, t_data *data);

// exit
	// exit.c
void	error_message(char *msg, int fd, int code);
void	clean_exit(t_data *data, char *msg, int fd, int code);
void	err_msg_cd(const char *path, t_data *data);
void	clean_cmd_exit(t_data *data, int fdi, int fdo, char *msg);
	// free_tree.c
void	free_from_cmd(t_cmd *cmd);
	// free.c
void	free_before_exit(t_data *data);
void	free_tab(char **tab, int start);
void	free_cmd_tree(t_data *data);
void	free_and_null(void *data);
void	free_tab_test(char **tab, int start);

// init
	// init_structs.c
void	init_data(t_data *data);
t_cmd	*init_cmd(void);
int		init_pipe(t_pipe **pipe);
int		init_redir(t_redir **redir);
int		init_exec(t_exec **exec);
	// init.c
void	init(char **enp, t_data *data);
	// signal.c
void	setup_signal(int mode);

// lexing
	// lex_exec.c
t_cmd	*lst_build_exec(char **cmd_arr, int end_i);
	// lex_pipe.c
t_cmd	*lst_build_from_pipe(char **cmd_arr, int pipe_i);
	// lex_redir.c
t_cmd	*lst_build_from_redir(char **cmd_arr, int end_i, int cnt);
	// lexer.c
void	remove_quotes(char *word, char *t);
int		lexer(char **cmd_arr, t_data *data);

// parsing
	// clean_tree.c
int		clean_tree(t_data *data, t_cmd *cmd);
	// handle_dollar.c
int		handle_dollar(char **cmd_arr, char **enp);
	// parse_and_lex.c
int		parse_and_lex(char **line, t_data *data);
	// parsing_utils.c
void	skip_quotes_ptr(char **s);
int		is_special_char(char c);
void	skip_spe_char(char **s);
int		is_in_single_quotes(char *s, char *t);
int		get_char_token(char *c);
	// split.c
void	free_mid_tab(char **tab, int i);
char	**split(char *s);

// minishell.c
int		getset_exit_code(int new_code);

#endif
