NAME			= fdf
SRC				= src
INC				= inc


all:
	@echo "\033[32mft_select compiling...\033[0m"
	@gcc $(SRC)/main.c $(SRC)/mapparser.c \
	$(SRC)/pretty_terminal.c $(SRC)/tty_configure.c \
	libft/libft.a -I inc \
	-Lminilibx_macos -lmlx \
	-ltermcap \
	-framework OpenGL \
	-framework AppKit \
	-o fdf
	@echo "\033[33mCompiled!\033[0m"
