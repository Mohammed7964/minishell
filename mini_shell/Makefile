#------------------------------Source Files------------------------------------#
SRC = parssing/tokenization.c parssing/ft_split.c parssing/ft_strcmp.c \
	parssing/libft.c parssing/main.c parssing/syntax_error.c parssing/ft_strjoin.c \
	parssing/joining.c

#------------------------------Object Files------------------------------------#
OBJ = $(SRC:.c=.o)

#------------------------------Compiler and Flags------------------------------#
CC = cc
CFLAGS = -Wall -Wextra -Werror

#------------------------------Includes and Executables------------------------#
NAME = minishell

READLINE_COMPILE = -I$(shell brew --prefix readline)/include
READLINE_LINK = -lreadline -L$(shell brew --prefix readline)/lib

#------------------------------Rules-------------------------------------------#
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE_LINK)

%.o: %.c includes/mini_shell.h
	@$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@
	@echo █▀▄▀█ ░▀░ █▀▀▄ ░▀░ █░░█ █▀▀ █░░ █░░
	@echo █░▀░█ ▀█▀ █░░█ ▀█▀ █▀▀█ █▀▀ █░░ █░░
	@echo ▀░░░▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀▀▀

#------------------------------Clean-------------------------------------------#
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

#------------------------------Rebuild-----------------------------------------#
re: fclean all
