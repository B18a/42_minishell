NAME = exec
CC = cc
CFLAGS =  -Wall -Werror -Wextra
SRCS = handler.c \
		get_path.c \
		exec_cmd.c \
		exec_outfile.c \
		exec_infile.c \
		exec_append.c \
		exec_pipe.c \
		get_list.c \
		main.c \
		get_next_line.c \
		exec_heredoc.c



GREEN = \033[0;32m
RED = \033[0;31m
DEFAULT = \033[0m

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

OBJS = $(SRCS:.c=.o)

SUBDIR = ../../libs/libft

all: $(NAME)

$(NAME) : $(SUBDIR) $(OBJS)
	@$(MAKE) -C $(SUBDIR)
	@$(CC) $(OBJS) -L$(SUBDIR) -lft -lreadline -o $(NAME)
	@echo "$(GREEN)minishell make abgeschlossen$(DEFAULT)"

$(SUBDIR):
	@$(MAKE) -C $(SUBDIR)

#	rm test_no
#	rm test_in_yes
rm:
	@rm test_yes

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(SUBDIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(SUBDIR) fclean
	@echo "$(RED)minishell fclean abgeschlossen$(DEFAULT)"

re: fclean all
