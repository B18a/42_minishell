# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 15:31:09 by ajehle            #+#    #+#              #
#    Updated: 2024/05/03 13:43:42 by ajehle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME				= minishell
CC					= cc
REMOVE				= rm -rf
SRC_DIR				= src
OBJ_DIR				= ./obj
INC_DIR				= include
CFLAGS				= -I $(INC_DIR) -Wall -Werror -Wextra
LIBREADLINE			= -lreadline

# looking for files in subdirectories
vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)

# INTERNAL FUNCTIONS
PARSER	=	shell.c \
				debug.c \
				free.c \
				get_input.c \
				parser_helper.c \
				parser_no_pipe.c \
				parser_pipes.c \
				parser_tree.c \
				parser.c \
				print_tree.c \
				sorting.c \
				tokenizer_helper_2.c \
				tokenizer_helper.c \
				tokenizer.c \

EXEC	=	handler.c \
				get_path.c \
				exec_cmd.c \
				exec_outfile.c \
				exec_infile.c \
				exec_append.c \
				exec_pipe.c \
				get_next_line.c \
				exec_heredoc.c \
				exec_builtin.c

BUILTIN	=	builtins.c \
				expander.c \
				env_list_helper.c \
				ft_env.c \
				ft_export.c \
				ft_export_no_args.c \
				ft_unset.c \
				ft_pwd.c \
				ft_cd.c

SRCS	=	$(addprefix parser/, $(PARSER)) \
			$(addprefix exec/, $(EXEC)) \
			$(addprefix builtin/, $(BUILTIN))

# Colors
YELLOW := "\033[0;33m"
CYAN := "\033[0;36m"
BLUE := "\033[0;34m"
GREEN := "\033[0;32m"
RED := "\033[0;31m"
RESET := "\033[0m"

# --- EXTERNAL LIBRARYS START --- #
# FT_LIBFT Resources
FT_LIBFT_DIR		= libs/libft
FT_LIBFT			= $(FT_LIBFT_DIR)/libft.a

# EXTERNAL LIBRARY
LIB_FT_LIBFT		= -L$(FT_LIBFT_DIR) -lft

# ALL LIBS
LIBS				= $(LIB_FT_LIBFT)
LIBS_NAME			=  $(FT_LIBFT)
# --- EXTERNAL LIBRARYS END --- #

# EXTERNAL LIBRARYS RULE (1 for each lib)
$(FT_LIBFT) :
	$(MAKE) bonus -C $(FT_LIBFT_DIR)

# INTERNAL OBJECT
OBJECTS	= $(addprefix src/, $(SRCS:.c=.o))
# OBJECTS	= $(addprefix src/, $(notdir $(SRCS:.c=.o)))

# INTERNAL RULE
$(NAME) : $(LIBS_NAME) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) $(LIBREADLINE) -o $(NAME)
	@echo $(GREEN) "ALL DONE" $(RESET)

# DIRECTORY
$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all :  $(NAME)

clean :
	$(MAKE) -C $(FT_LIBFT_DIR) clean
	rm src/exec/*.o
	rm src/parser/*.o
	rm src/builtin/*.o
	@echo $(YELLOW) "CLEAN DONE" $(RESET)

fclean : clean
	$(MAKE) -C $(FT_LIBFT_DIR) fclean
	@$(REMOVE) $(NAME)
	@echo $(RED) "FCLEAN DONE" $(RESET)

re : fclean all

.PHONY : all clean fclean re
