# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andreasjehle <andreasjehle@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 15:31:09 by ajehle            #+#    #+#              #
#    Updated: 2024/03/27 18:46:50 by andreasjehl      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell
CC					= cc
REMOVE				= rm -rf
SRC_DIR				= src
SRC_DIR_AJEHLE		= src_ajehle
SRC_DIR_PSANGER		= src_psanger
OBJ_DIR				= ./obj
INC_DIR				= include
CFLAGS				= -Wall -Werror -Wextra -I $(INC_DIR)

# looking for files in subdirectories
vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)

# INTERNAL FUNCTIONS
FUNCTIONS	=	$(SRC_DIR)/main.c \
				$(SRC_DIR_AJEHLE)/main_ajehle.c \
				 $(SRC_DIR_PSANGER)/main_psanger.c \

# INTERNAL OBJECT
OBJECTS				= $(addprefix $(OBJ_DIR)/, $(notdir $(FUNCTIONS:.c=.o)))

# --- EXTERNAL LIBRARYS START --- #
# FT_PRINTF Resources
FT_PRINTF_DIR		= libs/ft_printf
FT_PRINTF			= $(FT_PRINTF_DIR)/libftprintf.a

# FT_LIBFT Resources
FT_LIBFT_DIR		= libs/libft
FT_LIBFT			= $(FT_LIBFT_DIR)/libft.a

# GET_NEXT_LINE Resources
GET_NEXT_LINE_DIR	= libs/get_next_line
GET_NEXT_LINE		= $(GET_NEXT_LINE_DIR)/libget_next_line.a

# EXTERNAL LIBRARY
LIB_FT_PRINTF		= -L$(FT_PRINTF_DIR) -lftprintf
LIB_FT_LIBFT		= -L$(FT_LIBFT_DIR) -lft
LIB_GET_NEXT_LINE	= -L$(GET_NEXT_LINE_DIR) -lget_next_line

# ALL LIBS
LIBS				= $(LIB_FT_PRINTF) $(LIB_FT_LIBFT) $(LIB_GET_NEXT_LINE)
LIBS_NAME			= $(FT_PRINTF) $(FT_LIBFT) $(GET_NEXT_LINE)
# --- EXTERNAL LIBRARYS END --- #

all :  $(NAME)

# INTERNAL RULE
$(NAME) : $(LIBS_NAME) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)

# EXTERNAL LIBRARYS RULE (1 for each lib)
$(FT_PRINTF) :
	$(MAKE) -C $(FT_PRINTF_DIR)
$(FT_LIBFT) :
	$(MAKE) bonus -C $(FT_LIBFT_DIR)
$(GET_NEXT_LINE) :
	$(MAKE) -C $(GET_NEXT_LINE_DIR)
	$(MAKE) bonus -C $(GET_NEXT_LINE_DIR)

# DIRECTORY
$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(SRC_DIR_AJEHLE)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(SRC_DIR_PSANGER)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(MAKE) -C $(FT_LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	$(MAKE) -C $(GET_NEXT_LINE_DIR) clean
	$(REMOVE) $(OBJECTS)
	$(REMOVE) $(OBJ_DIR)

fclean : clean
	$(MAKE) -C $(FT_LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean
	$(REMOVE) $(NAME)

re : clean all

.PHONY : all mlx_clone clean fclean re
