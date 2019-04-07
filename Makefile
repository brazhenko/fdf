NAME			= fdf
SRC				= src
INC				= inc


all:
	@echo "\033[32mlibft compiling...\033[0m"
	@make re --directory libft
	@echo "\033[33mCompiled!\033[0m"
	@echo "\033[32mfdf compiling...\033[0m"
	@clang -Wall -Wextra -Werror  $(SRC)/main.c $(SRC)/mapparser.c \
	$(SRC)/tty_configure.c $(SRC)/map_twister.c \
	$(SRC)/tty_print.c \
	$(SRC)/tupa_chill.c \
	$(SRC)/auto_coloring.c \
	$(SRC)/fdf_exit.c \
	$(SRC)/wu.c \
	$(SRC)/supps.c \
	$(SRC)/supps1.c \
	$(SRC)/supps2.c \
	libft/libft.a -I inc \
	-Lminilibx_macos -lmlx \
	-ltermcap \
	-framework OpenGL \
	-framework AppKit \
	-o fdf
	@echo "\033[33mCompiled!\033[0m"
