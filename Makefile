CC = gcc
CC_WIN = x86_64-w64-mingw32-gcc

CFLAGS = -Wall -Wextra -Werror -lSDL2
LIBS = -lSDL2 -L. -lm

SDL2_PATH = /home/agruet/SDL2-2.30.8/x86_64-w64-mingw32

CFLAGS_WIN = -Wall -Wextra -Werror -L. -I$(SDL2_PATH)/include -L$(SDL2_PATH)/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -m64 -lm -static -lwinmm -lole32 -luuid -lcomdlg32 -lversion -limm32 -lsetupapi -lcfgmgr32 -loleaut32

DIR = game_of_life_no_grid
OBJ = $(DIR)/cells.o $(DIR)/game.o $(DIR)/utils.o $(DIR)/sdl.o
OBJ_WIN = $(DIR)/win_win.o $(DIR)/cells_win.o $(DIR)/game_win.o $(DIR)/utils_win.o $(DIR)/sdl_win.o

NAME = GameOfLife
NAME_WIN = GameOfLife.exe

RC = x86_64-w64-mingw32-windres
RES_FILE = resource.rc
RES_OBJ = resource.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBS)

exe: $(OBJ_WIN) $(RES_OBJ)
	$(CC_WIN) -o $(NAME_WIN) $(OBJ_WIN) $(RES_OBJ) $(CFLAGS_WIN)

$(RES_OBJ): $(RES_FILE)
	$(RC) $(RES_FILE) -o $(RES_OBJ)

%_win.o: %.c
	$(CC_WIN) $(CFLAGS_WIN) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_WIN) $(RES_OBJ)

fclean: clean
	rm -f $(NAME) $(NAME_WIN)

re: fclean all

.PHONY: all exe clean fclean re
