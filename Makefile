NAME			= fdf


all:
	gcc main.c src/mapparser/mapparser.c libft/libft.a -Iinc -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit -o fdf
