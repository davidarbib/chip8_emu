CC = gcc-13
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c2x
LDFLAGS =

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(SANITIZE), 1)
	CFLAGS += -fsanitize=address
endif

NAME = chip8
OBJS_DIR = ./objs/
SRCS_DIR = ./src/
INCS_DIRS = ./includes/
SRCS = chip8.c \
       stack.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)
INCS = $(addprefix -I, $(INCS_DIRS))
    
vpath %.c $(SRCS_DIR)
.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ 
	mkdir -p ./build
	cp compile_commands.json build/

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@		

clean:
	rm -rf $(OBJS_DIR) 

fclean: clean
	rm -f $(NAME)

re: fclean all
