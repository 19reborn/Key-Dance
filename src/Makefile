CC = g++
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
CFLAGS = -Wall -std=c++11 -Wno-missing-braces -s -O1 -I../include/ -L../lib/ $(LIBS)
BUTTON_H = ../include/button.h
INTERFACE_H = ../include/interface.h
OBJ_INTERFACES = interfaces/interface_main.o interfaces/interface_test.o interfaces/public.o
OBJS = $(OBJ_INTERFACES) button.o

interfaces/interface_main.o: interfaces/interface_main.cc $(INTERFACE_H)
	$(CC) -c $< $(CFLAGS) -o $@
interfaces/interface_test.o: interfaces/interface_test.cc $(INTERFACE_H)
	$(CC) -c $< $(CFLAGS) -o $@
interfaces/public.o: interfaces/public.cc $(INTERFACE_H)
	$(CC) -c $< $(CFLAGS) -o $@

button.o: button.cc $(INTERFACE_H) $(BUTTON_H)
	$(CC) -c $< $(CFLAGS) -o $@

game: main.cc $(INTERFACE_H) $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%: %.cc
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm -f $(OBJS) game
