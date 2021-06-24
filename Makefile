WIN = true
CC = gcc
CFLAG = -Wall -Wextra -Werror -pedantic -std=c18
CLIB = -L lib -I include -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
EXEC = bin/Morpion

SRC = $(wildcard src/*.c src/Test/*.c src/bool/*.c src/Image/*.c src/Text/*.c src/SetingFile/*.c src/Game/*.c src/Divers/*.c src/Player/*.c src/Grille/*.c src/Graphic/*.c src/IA/*.c src/Button/*.c)
OBJ = $(SRC:.c=.o)

ifeq ($(WIN), true)
	ICO = src/Logo.o
endif

all  : $(EXEC)

%.o : %.c
	$(CC) $(CFLAG) -o $@ -c $< $(CLIB)

$(EXEC) : $(OBJ)
	$(CC) $(CFLAG) -o $@ $^ $(ICO) $(CLIB)

clean : 
	rm -rf *.o


# Variable Speciale

# $@ Non de la cible
# $< Nom premiere dependance
# $^ Liste dependance
# $? Liste dependance plus recente que la cible
# $* Nom du fichier sans son extension

