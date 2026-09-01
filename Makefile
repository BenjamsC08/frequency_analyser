CC = cc
FLAGS = -g -Wall -Wextra -Werror -pthread -no-pie
NAME = freq
SRCS = srcs/data_node_utils.c srcs/export.c srcs/hex_parsing.c srcs/inits.c srcs/multiThread.c srcs/routines.c srcs/list_utils.c srcs/main.c srcs/config_utils.c
OBJ = $(SRCS:.c=.o)
LIB_PATH = -L.
LIB_NAME = -lft
INCLUDE_PATH = -Iincludes
VALID = \033[1;32m
NOTVALID = \033[1;31m
LOADING = \033[3;33m
RESET = \033[0m

all: $(NAME)
	@printf "$(VALID) - Done \t\t\t✅$(RESET)\n"

srcs/%.o: srcs/%.c
	$(CC) $(FLAGS) $(INCLUDE_PATH) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIB_PATH) $(LIB_NAME) $(INCLUDE_PATH) -o $@
	@printf "$(VALID) - $(NAME): compilation terminée \t✅$(RESET)\n"

clean:
	@rm -f $(OBJ)
	@printf "$(VALID) - clean \t\t\t✅$(RESET)\n"

fclean: clean
	@rm -f $(NAME) *.json
	@printf "$(VALID) - fclean \t\t\t✅$(RESET)\n"

reset:
	@rm -rf config

freset: fclean reset

re: fclean all

listC:
	@find -wholename "./srcs/*.c" | cut -c 3- | tr '\n' ' '

nbC:
	@find -wholename "./srcs/*.c" | wc -l

.PHONY: all clean fclean re clist cnb
