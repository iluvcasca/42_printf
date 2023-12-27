C_FILES = $(filter-out $(wildcard test*.c), $(wildcard ft_*.c))
O_FILES = $(C_FILES:%.c=build/%.o)
B_C_FILES = $(C_FILES)
B_O_FILES = $(B_C_FILES:%.c=build/%.o)
C_FLAGS = -Wall -Werror -Wextra 
NAME = libftprintf.a 

.PHONY: all clean fclean re
.DEFAULT: all

all: $(NAME)

$(NAME): $(O_FILES)
	ar -rcs $(NAME) $^ 

build:
	@mkdir -p build

build/%.o: %.c | build
	cc $(C_FLAGS) -c $< -o $@

clean:
	-rm -f $(O_FILES)
	-rm -f $(B_O_FILES)
	-rm -rf build

fclean: clean
	-rm -f $(NAME)
	-rm -f libft.so
	-rm -f *.out

re: fclean all

bonus: fclean all

