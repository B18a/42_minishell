# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 15:31:09 by ajehle            #+#    #+#              #
#    Updated: 2024/05/24 23:06:28 by ajehle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME				:= minishell
CC					:= cc
REMOVE				:= rm -rf
SRC_DIR				:= src
CFLAGS				:=  -I include -Wall -Werror -Wextra
LIBREADLINE			:= -lreadline
VPATH	:=	src \
			src/builtin \
			src/exec \
			src/parser \
			include

# INTERNAL FUNCTIONS
SRCS	:=		shell.c \
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
				ft_expand.c \
				ft_expand_helper.c \
				handler.c \
				get_path.c \
				exec_cmd.c \
				exec_outfile.c \
				exec_infile.c \
				exec_append.c \
				exec_pipe.c \
				get_next_line.c \
				exec_heredoc.c \
				exec_builtin.c \
				builtins.c \
				expander.c \
				env_list_helper.c \
				ft_env.c \
				ft_export.c \
				ft_export_no_args.c \
				ft_unset.c \
				ft_pwd.c \
				ft_cd.c \
				ft_echo.c \
				ft_exit.c \
				mid_exit_free.c \
				helper_func.c \
				tokenizer_psanger.c \
				split_with_quotes.c \
				join_two_d_arr.c \
				signals_in_child.c \
				cpy_input_tok.c \
				new_input_len.c \
				expand_input.c \
				tokenizer_psanger_helper.c \
				expander_get_new_len.c \
				expander_cpy.c \
				check_tok.c \
				get_tok_str.c \
				handle_heredoc.c \

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
OBJ_DIR	:= obj
OBJECTS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# INTERNAL RULE
$(NAME) : $(LIBS_NAME) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) $(LIBREADLINE) -o $(NAME)
	@echo $(GREEN) "ALL DONE" $(RESET)

# DIRECTORY

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -c $< -o $@

all :  $(NAME)

clean :
	$(MAKE) -C $(FT_LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	@echo $(YELLOW) "CLEAN DONE" $(RESET)

fclean : clean
	$(MAKE) -C $(FT_LIBFT_DIR) fclean
	@$(REMOVE) $(NAME)
	@echo $(RED) "FCLEAN DONE" $(RESET)

re : fclean all

.PHONY : all clean fclean re
