WIN = true
CONSOLE = false

CC = gcc
CD = -g
CFLAG = -O3 -Wall -Wextra -Werror -pedantic -std=c18
EXEC = bin/Morpion

SRC = $(wildcard src/*.c src/Test/*.c src/bool/*.c src/Image/*.c src/Text/*.c src/SetingFile/*.c src/Game/*.c src/Divers/*.c src/Player/*.c src/Grille/*.c src/Graphic/*.c src/IA/*.c src/Button/*.c)
OBJ = $(SRC:.c=.o)

ifeq ($(WIN), true)
	ICO = src/Logo.o
	CLIB = -L lib -I include -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
	ifeq ($(CONSOLE), false)
		CWINDOW = -mwindows
	endif
else
	CLIB = `sdl2-config --cflags --libs`
endif

all  : $(EXEC)

%.o : %.c
	$(CC) $(CD) $(CFLAG) -o $@ -c $< $(CLIB)

$(EXEC) : $(OBJ)
	$(CC) $(CD) $(CFLAG) -o $@ $^ $(ICO) $(CLIB) $(CWINDOW)

clean : 
	rm -rf *.o


# Variable Speciale

# $@ Non de la cible
# $< Nom premiere dependance
# $^ Liste dependance
# $? Liste dependance plus recente que la cible
# $* Nom du fichier sans son extension

