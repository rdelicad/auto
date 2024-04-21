CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
NAME = auto
SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

vpath %.c $(SRC_DIR)

all: $(NAME)

create_obj:
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c | create_obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	rm -rf *.dSYM
	rm -f .DS_Store
	rm -rf directorio

re: fclean all

.PHONY: all clean fclean