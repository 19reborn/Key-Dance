CC = gcc
CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1 -D_DEFAULT_SOURCE -I/usr/local/include -I. -I/home/game/raylib/src -I/home/game/raylib/src/external -L. -L/usr/local/lib -L/home/game/raylib/src -L/home/game/raylib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -DPLATFORM_DESKTOP

game: game.c model.c init.c update.c render.c
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm -f $(OBJS) game
