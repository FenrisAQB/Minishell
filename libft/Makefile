# Output file name
NAME			= libft.a

# Define sources
SRC				= ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isascii.c \
					ft_isprint.c \
					ft_strlen.c \
					ft_memset.c \
					ft_bzero.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_strlcpy.c \
					ft_strlcat.c \
					ft_toupper.c \
					ft_tolower.c \
					ft_strchr.c \
					ft_strrchr.c \
					ft_strncmp.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_strnstr.c \
					ft_atoi.c \
					ft_calloc.c \
					ft_strdup.c \
					ft_substr.c \
					ft_strjoin.c \
					ft_strtrim.c \
					ft_split.c \
					ft_itoa.c \
					ft_strmapi.c \
					ft_striteri.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c \
					ft_printf.c \
					write_alpha.c \
					write_num.c \
					check_format.c \
					get_next_line.c \
					get_next_line_utils.c \

# Define sources dir
SRC_DIR			= ./srcs/

# Full sources path
SRCS			= $(addprefix $(SRC_DIR), $(SRC))

# Define object files
OBJS			= $(SRCS:.c=.o)

# Compilation message
TOT_FILES		= $(words $(SRC))
COMPILED_FILES	= 0
MESSAGE			= "Compiling: $(COMPILED_FILES)/$(TOT_FILES) ($(shell expr $(COMPILED_FILES) \* 100 / $(TOT_FILES))%)"

# Text formatting
GREEN			= \033[32m
RED				= \033[31m
BLUE			= \033[34m
GREY			= \033[90m
BG_BLUE			= \033[44m
ENDCOLOR		= \033[0m
BOLD			= \033[1m

# Texts
START			= echo "$(BLUE)$(BOLD)Compilation of $(NAME) started\n$(ENDCOLOR)"
END				= echo "$(GREEN)$(BOLD)✔ Compilation finished\n$(ENDCOLOR)"
CLEAN_MSG		= echo "$(RED)$(BOLD)✖ Deleting library object files\n$(ENDCOLOR)"
FCLEAN_MSG		= echo "$(RED)$(BOLD)✖ Deleting library\n$(ENDCOLOR)"

# Define bar variables
BAR_LEN			= 70
BAR				= $(shell expr $(COMPILED_FILES) \* $(BAR_LEN) / $(TOT_FILES))

# Header file
HEAD			= ./includes/libft.h

# Library creation command
AR				= ar rcs

# Cleaning command
RM				= rm -f

# Compiler
CC				= gcc

# Compiler flags
CFLAGS			= -Wall -Wextra -Werror -g

# Define all
all:			logo $(NAME) end

# Define logo
logo:
				@tput setaf 5; tput bold; cat ../ascii_art/libft; echo "\n"; tput init;

# Define start logo
start:
				@tput setaf 4; cat ../ascii_art/CDRX;  echo "\n"; tput init;

# Define end logo
end:
				@tput setaf 2; tput bold; cat ../ascii_art/done; echo "\n"; tput init;

# Create object files
%.o : %.c

				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
				$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
				@printf "$(BLUE)%s\r\n$(ENDCOLOR)" $(MESSAGE)
				@sleep 0.1
				@printf "$(BG_BLUE)%*s$(ENDCOLOR)\r" $(BAR) " "
				@printf "\033[F"

# Create libft file
$(NAME):		$(OBJS)
				@printf "\n\n"
				@$(AR) $(NAME) $(OBJS)
				@$(END)

# Clean object files
clean:
				@$(CLEAN_MSG)
				@$(RM) $(OBJS)
				@tput setaf 1; tput bold; cat ../ascii_art/trash; tput init;
				@tput setaf 2; tput bold; cat ../ascii_art/gone; echo "\n"; tput init;

# Clean object files and library file
fclean:			clean
				@$(FCLEAN_MSG)
				@$(RM) $(NAME)
				@tput setaf 1; tput bold; cat ../ascii_art/trash; tput init;
				@tput setaf 2; tput bold; cat ../ascii_art/all_gone; tput init;

# Redo everything
re:				fclean all

# Avoid collisions with files named the same as commands
.PHONY:			all clean fclean re
