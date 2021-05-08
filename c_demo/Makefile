CC = gcc
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
CFLAGS = -Wall -std=c99 -Wno-missing-braces -s -O1 -Iinclude/ -Llib/ $(LIBS)
game: game.c model.c init.c update.c render.c
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm -f $(OBJS) game
