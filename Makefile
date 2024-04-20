# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 15:31:09 by ajehle            #+#    #+#              #
#    Updated: 2024/04/20 13:41:44 by ajehle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME				= minishell
CC					= cc
REMOVE				= rm -rf
SRC_DIR				= src
OBJ_DIR				= ./obj
INC_DIR				= include
CFLAGS				= -Wall -Werror -Wextra -I $(INC_DIR)
LIBREADLINE			= -lreadline

# looking for files in subdirectories
vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)

# INTERNAL FUNCTIONS
FUNCTIONS	=	$(SRC_DIR)/debug.c \
				$(SRC_DIR)/get_input.c \
				$(SRC_DIR)/get_path.c \
				$(SRC_DIR)/parser_helper.c \
				$(SRC_DIR)/parser.c \
				$(SRC_DIR)/print_tree.c \
				$(SRC_DIR)/shell.c \
				$(SRC_DIR)/tokenizer_helper.c \
				$(SRC_DIR)/tokenizer.c \

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
OBJECTS	= $(addprefix $(OBJ_DIR)/, $(notdir $(FUNCTIONS:.c=.o)))

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
	@$(REMOVE) $(OBJECTS)
	@$(REMOVE) $(OBJ_DIR)
	@echo $(YELLOW) "CLEAN DONE" $(RESET)

fclean : clean
	$(MAKE) -C $(FT_LIBFT_DIR) fclean
	@$(REMOVE) $(NAME)
	@echo $(RED) "FCLEAN DONE" $(RESET)

re : clean all
#re : fclean all

.PHONY : all clean fclean re
