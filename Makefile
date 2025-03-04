# Output file name
NAME			= minishell
#BNAME			= pipex_bonus

# Output file debugger name
DEBUG			= minishell_debug
#BDEBUG			= pipex_bonus_debug

# Define main file
MAINFILE		= ./minishell.c
#BMAINFILE		= ./bonus/pipex_bonus.c

# Define sources
SRC				= builtins/builtin_cd.c \
					builtins/builtin_echo.c \
					builtins/builtin_env.c \
					builtins/builtin_exit.c \
					builtins/builtin_export.c \
					builtins/builtin_pwd.c \
					builtins/builtin_unset.c \
					debug/debug_tree.c \
					debug/debug.c \
					env/env_utils.c \
					env/handle_env.c \
					exec/cmd_utils.c \
					exec/exec_cmd.c \
					exec/parse_tree.c \
					exec/pipe_cmd.c \
					exec/redir_cmd.c \
					exec/redir_for_builtin.c \
					exec/run_builtin.c \
					exec/run_cd.c \
					exec/run_cmd.c \
					exec/run_echo.c \
					exec/run_env.c \
					exec/run_export.c \
					exec/run_unset.c \
					exec/run_var.c \
					exec/var_utils.c \
					exit/exit.c \
					exit/free_tree.c \
					exit/free.c \
					init/init_structs.c \
					init/init.c \
					init/signal.c \
					lexing/lex_exec.c \
					lexing/lex_pipe.c \
					lexing/lex_redir.c \
					lexing/lexer.c \
					parsing/clean_tree.c \
					parsing/handle_dollar.c \
					parsing/parse_and_lex.c \
					parsing/parsing_utils.c \
					parsing/split.c \

#BSRC			= parse_and_init.c \
					exit.c \
					processes.c \
					cmd_utils.c \

#BSRC_2			= here_doc_bonus.c \

# Define sources dir
SRC_DIR			= ./srcs/
#BSRC_DIR		= ./bonus/srcs/

# Full sources paths
SRCS			= $(addprefix $(SRC_DIR), $(SRC))
#BSRCS			= $(addprefix $(SRC_DIR), $(BSRC))
#BSRCS_2			= $(addprefix $(BSRC_DIR), $(BSRC_2))

# Define targets requiring user input & targets for bonus
#INPUT_TARGETS	:= run debug bdebug brun
#BONUS_TARGETS	:= bonus brun bdebug

# Make flags for pretty output
export MAKEFLAGS	+= --no-print-directory

# Define uname
UNAME			= $(shell uname)

# Define libraries
LIBFT_DIR		= ./libft/
LIBFT			= $(addprefix $(LIBFT_DIR), libft.a)
MAKELIBFT		= @$(ENTER_DIR); cd $(LIBFT_DIR); $(MAKE)

# Define object files
OBJS			= $(SRCS:.c=.o)
OBJMAIN			= $(MAINFILE:.c=.o)
#BOBJS			= $(BSRCS:.c=.o)
#BOBJS_2			= $(BSRCS_2:.c=.o)
#BOBJMAIN		= $(BMAINFILE:.c=.o)

# Compilation message
TOT_FILES		= $(shell expr $(words $(SRC)) + 1)
#ifneq ($(filter $(MAKECMDGOALS), $(BONUS_TARGETS)),)
#TOT_FILES		= $(shell expr $(words $(SRC)) + 2)
#endif
COMPILED_FILES	= 0
MESSAGE			= "Compiling: $(COMPILED_FILES)/$(TOT_FILES) ($(shell expr $(COMPILED_FILES) \* 100 / $(TOT_FILES))%)"

# Text styling
GREEN			= \033[32m
RED				= \033[31m
BLUE			= \033[34m
GREY			= \033[90m
YELLOW			= \033[33m
BG_BLUE			= \033[44m
ENDCOLOR		= \033[0m
BOLD			= \033[1m

# Define arguments to use
#ifneq ($(filter $(MAKECMDGOALS), $(INPUT_TARGETS)),)
#ARGS				:= $(shell read -p "$(shell echo "$(YELLOW)$(BOLD)Please input your command: $(ENDCOLOR)")" args; echo $$args)
#endif

# Texts
START			= echo "$(BLUE)Compilation of $(NAME) started\n$(ENDCOLOR)"
END				= echo "$(GREEN)$(BOLD)✔ Compilation finished\n$(ENDCOLOR)"
CLEAN_MSG		= echo "$(RED)$(BOLD)✖ Deleting object files\n$(ENDCOLOR)"
FCLEAN_MSG		= echo "$(RED)$(BOLD)✖ Deleting program\n$(ENDCOLOR)"
ENTER_DIR		= echo "$(BLUE)➜$(ENDCOLOR)$(BOLD)  Entering directory$(RESET) $(YELLOW)$(LIBFT_DIR)$(ENDCOLOR)"
LEAVE_DIR		= echo "$(BLUE)➜$(ENDCOLOR)$(BOLD)  Leaving directory$(RESET) $(YELLOW)$(LIBFT_DIR)$(ENDCOLOR)"

# Define bar variables
BAR_LEN			= 70
BAR				= $(shell expr $(COMPILED_FILES) \* $(BAR_LEN) / $(TOT_FILES))

# Define includes
HEAD			= ./includes/minishell.h
#BHEAD			= ./bonus/includes/pipex_bonus.h

# Library creation command
AR				= ar rcs

# Cleaning command
RM				= rm -f

# Compiler / debugger
CC				= gcc
DEBUGGER		= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --verbose --suppressions=ignore_readline_leaks.supp --log-file=valgrind-out.txt


# Compiler / debugger flags
CFLAGS			= -Wall -Wextra -Werror -g
DFLAGS			= -ggdb3

# Define all
all:			logo start start2 $(NAME) end

# Define bonus
#bonus:			blogo start $(BNAME) end

# Define logo
logo:
				@tput setaf 5; tput bold; cat ./ascii_art/minishell; echo "\n"; tput init;

# Define bonus logo
#blogo:
#				@tput setaf 5; cat ./ascii_art/pipex_bonus; echo "\n"; tput setaf sgr0;

# Define start visual
start:
				@tput setaf 4; cat ./ascii_art/Fenris;  echo "\n"; tput init;
start2:
				@tput setaf 4; cat ./ascii_art/CDRX;  echo "\n"; tput init;

# Define end visual
end:
				@tput setaf 2; tput bold; cat ./ascii_art/done; echo "\n"; tput init;

# Create object files
%.o : %.c
				@$(CC) $(CFLAGS) -c $< -o $@
				$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
				@printf "$(BLUE)%s\r\n$(ENDCOLOR)" $(MESSAGE)
				@sleep 0.1
				@printf "$(BG_BLUE)%*s$(ENDCOLOR)\r" $(BAR) " "
				@printf "\033[F"

# Create libraries
lib:
				@$(MAKELIBFT) all;
				@$(LEAVE_DIR)

# Create program file
$(NAME):		lib $(OBJMAIN) $(OBJS)
				@printf "\n\n"
				@$(CC) $(OBJS) $(OBJMAIN) $(LIBFT) -lreadline -o $(NAME)
				@$(END)

# Create bonus program file
#$(BNAME):		lib $(BOBJMAIN) $(BOBJS) $(BOBJS_2)
#				@$(CC) $(BOBJS) $(BOBJS_2) $(BOBJMAIN) $(LIBFT) -o $(BNAME)

# Create program file for debugging
$(DEBUG):		lib $(OBJMAIN) $(OBJS)
				@$(CC) $(DFLAGS) $(OBJS) $(OBJMAIN) $(LIBFT) -lreadline -o $(DEBUG)

# Create bonus program file for debugging
#$(BDEBUG):		lib $(BOBJMAIN) $(BOBJS) $(BOBJS_2)
#				@$(CC) $(DFLAGS) $(BOBJS) $(BOBJS_2) $(BOBJMAIN) $(LIBFT) -o $(BDEBUG)

# Run program
run:			logo start start2 $(NAME) end
				./$(NAME)

# Run bonus program
#brun:			logo blogo start $(BNAME) end
#				./$(BNAME) $(ARGS)

# Debug program
debug:			logo start start2 $(DEBUG) end
				@$(DEBUGGER) ./$(DEBUG)

# Debug bonus
#bdebug:			logo blogo start $(BDEBUG) end
#				@$(DEBUGGER) ./$(BDEBUG) $(ARGS)

# Clean object files & if on linux rm valgrind-out.txt
clean:
				@$(CLEAN_MSG)
				@$(RM) $(OBJS)
				@$(RM) $(OBJMAIN)
#				@$(RM) $(BOBJS)
#				@$(RM) $(BOBJS_2)
#				@$(RM) $(BOBJMAIN)
				@if [ $(UNAME) = "Linux" ]; then $(RM) valgrind-out.txt; fi
				@tput setaf 1; tput bold; cat ./ascii_art/trash; tput init;
				@tput setaf 2; tput bold; cat ./ascii_art/gone; echo "\n"; tput init;
				@$(MAKELIBFT) clean;

# Clean object files and program file
fclean:			clean
				@$(FCLEAN_MSG)
				@$(RM) $(NAME)
				@$(RM) $(DEBUG)
#				@$(RM) $(BNAME)
#				@$(RM) $(BDEBUG)
				@tput setaf 1; tput bold; cat ./ascii_art/trash; tput init;
				@tput setaf 2; tput bold; cat ./ascii_art/all_gone; tput init;
				@$(MAKELIBFT) fclean;

# Redo everything
re:				fclean all

# Avoid collisions with files named the same as commands
.PHONY:			all clean fclean re run debug bonus
