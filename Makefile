NAME = cub3d



SRC = $(wildcard *.c)
SRC_libft = $(wildcard libft/*.c)
OBJECTS = $(SRC:.c=.o)
OBJECTS_LIBFT = $(SRC_libft:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror  #-no-pie -fsanitize=address -g3
MLX = -lmlx_Linux -lX11 -lXext  

all: $(NAME) 
	@rm -rf *.o
$(NAME): $(OBJECTS)  $(OBJECTS_LIBFT)
	@$(CC) $(OBJECTS)  $(MLX) $(OBJECTS_LIBFT) $(libft)  -o $(NAME)

%.o: %.c
	@$(CC) $(MLX) $(CFLAGS) -c -o $@ $< 

clean:
	@rm -f   $(OBJECTS)  $(OBJECTS_LIBFT) && rm -rf *.o > /dev/null
fclean: clean
	@rm -rf ./cub3d

re: fclean all

.PHONY: all clean  fclean re bonus

.SECONDARY: 
