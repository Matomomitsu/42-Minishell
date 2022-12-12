# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 08:46:02 by rlins             #+#    #+#              #
#    Updated: 2022/12/12 10:45:51 by rlins            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Collors
RESET 	= \033[0m
GREEN 	= \033[0;32m
RED 	= \033[0;31m

# Paths
PATH_SRC 		= ./src/
PATH_MAIN 		= $(PATH_SRC)main/
PATH_INIT 		= $(PATH_SRC)init/
PATH_UTIL 		= $(PATH_SRC)util/
PATH_EXEC 		= $(PATH_SRC)execution/
PATH_RED 		= $(PATH_SRC)redirection/
PATH_ENV 		= $(PATH_SRC)env/
PATH_BUILTINS 	= $(PATH_SRC)builtins/
PATH_LEXER		= $(PATH_SRC)lexer/
PATH_PARSER		= $(PATH_SRC)parser/
PATH_OBJS 		= ./objs/

INC_PATH 		= ./include/

# Libft files and directories
LIBFT_PATH 		= ./lib/libft/
LIBFT 			= ./lib/libft.a

# Compilation
CC = gcc

# Compilation flags
CFLAGS = -g -Wall -Werror -Wextra

#Chedk Leak memory
LEAK = valgrind --leak-check=full --show-leak-kinds=all \
	--trace-children=yes --suppressions=readline.supp --track-origins=yes -s

RM			= rm -rf
NO_PRINT	= --no-print-directory
READ_LN		= -l readline

INCLUDE = -I $(INC_PATH) -I $(LIBFT_PATH)

SRCS =	$(PATH_MAIN)main.c \
		$(PATH_INIT)init.c \
		$(PATH_INIT)init_cmds.c \
		$(PATH_INIT)init_cmd.c \
		$(PATH_INIT)init_validation.c \
		$(PATH_INIT)prompt.c \
		$(PATH_INIT)init_structure.c \
		$(PATH_UTIL)exit.c \
		$(PATH_UTIL)signal.c \
		$(PATH_UTIL)debug.c \
		$(PATH_UTIL)error_handler.c \
		$(PATH_UTIL)sanitization.c \
		$(PATH_UTIL)sanitization_partial.c \
		$(PATH_UTIL)pipe.c \
		$(PATH_EXEC)exec_handler.c \
		$(PATH_EXEC)exec_partial.c \
		$(PATH_RED)redirection_handler.c \
		$(PATH_RED)rd_output_handler.c \
		$(PATH_RED)rd_input_handler.c \
		$(PATH_RED)rd_heredoc.c \
		$(PATH_RED)io_handler.c \
		$(PATH_UTIL)split_args.c \
		$(PATH_ENV)env.c \
		$(PATH_ENV)env_partial.c \
		$(PATH_BUILTINS)builtins_handler.c \
		$(PATH_BUILTINS)cmd_exit.c \
		$(PATH_BUILTINS)cmd_pwd.c \
		$(PATH_BUILTINS)cmd_cd.c \
		$(PATH_BUILTINS)cmd_env.c \
		$(PATH_BUILTINS)cmd_export.c \
		$(PATH_BUILTINS)cmd_unset.c \
		$(PATH_BUILTINS)cmd_echo.c \
		$(PATH_LEXER)lexer.c \
		$(PATH_LEXER)complete_lexer.c \
		$(PATH_LEXER)handle_lexer_errors.c \
		$(PATH_LEXER)handle_parenthesis.c \
		$(PATH_LEXER)handle_redirections.c \
		$(PATH_LEXER)handle_operators.c \
		$(PATH_LEXER)quotes_error.c \
		$(PATH_PARSER)parser.c \
		$(PATH_PARSER)complete_parser.c \
		$(PATH_PARSER)redirections.c \
		$(PATH_PARSER)complete_redirections.c \
		$(PATH_PARSER)rm_redirection.c \
		$(PATH_PARSER)copy_cmd.c \
		$(PATH_PARSER)handle_env.c \
		$(PATH_PARSER)find_dollar_sign.c \
		$(PATH_PARSER)find_export_cmd.c \
		$(PATH_PARSER)rm_spaces.c \
		$(PATH_PARSER)complete_split.c \
		$(PATH_PARSER)parse_path.c

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRCS))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCLUDE) $(LIBFT) $(READ_LN)
	@echo "$(GREEN)Build Successful$(RESET)"

$(PATH_OBJS)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)main/
	@mkdir -p $(PATH_OBJS)init/
	@mkdir -p $(PATH_OBJS)util/
	@mkdir -p $(PATH_OBJS)execution/
	@mkdir -p $(PATH_OBJS)redirection/
	@mkdir -p $(PATH_OBJS)env/
	@mkdir -p $(PATH_OBJS)builtins/
	@mkdir -p $(PATH_OBJS)lexer/
	@mkdir -p $(PATH_OBJS)parser/
	@$(CC) $(CFLAGS) $(INCLUDE) -I. -c $< -o $@

# Libft rule
$(LIBFT):
	@make -C $(LIBFT_PATH) $(NO_PRINT)

clean:
	@echo "$(RED)Cleaning objects...$(RESET)"
	@$(RM) $(PATH_OBJS)
	@make -C $(LIBFT_PATH) clean $(NO_PRINT)
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo  "$(RED)Cleaning all...$(RESET)"
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean $(NO_PRINT)
	@echo "$(RED)Cleaning binaries...$(RESET)"
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

run:
	make re && ./minishell

valgrind:
	$(LEAK) ./minishell

.PHONY: all run re clean fclean
