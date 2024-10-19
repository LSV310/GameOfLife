CC = gcc
CC_WIN = x86_64-w64-mingw32-gcc

CFLAGS = -Wall -Wextra -Werror -lSDL2
LIBS = -lSDL2 -L. -lm

SDL2_INCLUDE = /home/agruet/SDL2-2.30.8/x86_64-w64-mingw32/include
SDL2_LIB = /home/agruet/SDL2-2.30.8/x86_64-w64-mingw32/lib

CFLAGS_WIN = -Wall -Wextra -Werror -fno-stack-protector -L. -I$(SDL2_INCLUDE) -L$(SDL2_LIB) -lmingw32 -lSDL2main -lSDL2 -mwindows -m64 -lm

DIR = game_of_life_no_grid
OBJ = $(DIR)/cells.o $(DIR)/game.o $(DIR)/utils.o $(DIR)/sdl.o
OBJ_WIN = $(DIR)/win_win.o $(DIR)/cells_win.o $(DIR)/game_win.o $(DIR)/utils_win.o $(DIR)/sdl_win.o

NAME = GameOfLife
NAME_WIN = GameOfLife.exe

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBS)

exe: $(OBJ_WIN)
	$(CC_WIN) -o $(NAME_WIN) $(OBJ_WIN) $(CFLAGS_WIN)

%_win.o: %.c
	$(CC_WIN) $(CFLAGS_WIN) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_WIN)

fclean: clean
	rm -f $(NAME) $(NAME_WIN)

re: fclean all

.PHONY: all clean fclean re exe
