CC = g++
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
CFLAGS = -Wall -std=c++11 -Wno-missing-braces -s -O1 -Iinclude/ -Llib/ $(LIBS)

game: main.cc interface.cc interface.h button.cc
	$(CC) -o $@ $^ $(CFLAGS)

%: %.cc
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm -f $(OBJS) game
