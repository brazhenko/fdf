NAME			= fdf
SRC				= src
INC				= inc


all:
	@echo "\033[32mft_select compiling...\033[0m"
	@gcc $(SRC)/main.c $(SRC)/mapparser.c libft/libft.a -I inc \
	-Lminilibx_macos -lmlx \
	-framework OpenGL \
	-framework AppKit \
	-o fdf
	@echo "\033[33mCompiled!\033[0m"
