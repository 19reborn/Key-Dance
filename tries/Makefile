CC = g++
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
CFLAGS = -Wall -std=c++11 -Wno-missing-braces -s -O1 -Iinclude/ -Llib/ $(LIBS)

3D_shader: 3D_shader.cc
	$(CC) -o $@ $^ $(CFLAGS)
maze: maze1.cc
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm -f $(OBJS) game
