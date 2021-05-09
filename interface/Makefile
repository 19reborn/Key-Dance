CC = g++
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
CFLAGS = -Wall -std=c++11 -Wno-missing-braces -s -O1 -Iinclude/ -Llib/ $(LIBS)
BUTTON_H = include/button.h
INTERFACE_H = include/interface.h
INTERFACES = interfaces/interface_main.o interfaces/interface_modeswitch.o interfaces/interface_musicswitch.o interfaces/interface_test.o

interfaces/interface_main.o: interfaces/interface_main.cc $(INTERFACE_H)
	$(CC) -c $< $(CFLAGS) -o $@
interfaces/interface_modeswitch.o: interfaces/interface_modeswitch.cc $(INTERFACE_H)
	$(CC) -c $< $(CFLAGS) -o $@
interfaces/interface_musicswitch.o: interfaces/interface_musicswitch.cc $(INTERFACE_H)
	$(CC) -c $< $(CFLAGS) -o $@
interfaces/interface_test.o: interfaces/interface_test.cc $(INTERFACE_H)
	$(CC) -c $< $(CFLAGS) -o $@

button.o: button.cc $(INTERFACE_H) $(BUTTON_H)
	$(CC) -c $< $(CFLAGS) -o $@

game: main.cc $(INTERFACE_H) button.o $(INTERFACES)
	$(CC) -o $@ $^ $(CFLAGS)

%: %.cc
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm -f $(OBJS) game
