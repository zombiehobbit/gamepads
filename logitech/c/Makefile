# make file edited
# NOTE: -g is for extra debug headers.  I need to use gdb 

# added c flags.  I want to include some extra libs ~Dillon
CFLAGS = -Wall -Wextra -c -g # defult flgas
# link for the json libeary 
CFLAGS += $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c)


CC=gcc # use GCC unless otherewise stated 

#etest: main.o logitech.o
#	g++ -o etest main.o logitech.o
etest: main.o gamepad.o tcp_client.o
	g++ -o etest main.o gamepad.o tcp_client.o


#main.o: main.c logitech.h
#	gcc -Wall -Wextra -c main.c

main.o: main.c gamepad.h
#	gcc -Wall -Wextra -c -g main.c

#logitech.o: logitech.c logitech.h
#	gcc -Wall -Wextra -c logitech.c

gamepad.o: gamepad.c gamepad.h
#	gcc -Wall -Wextra -c -g gamepad.c

# NOTE: for some reason this isn't loading
# UPDATE: I think it's working now
# build rules for the tcp_client
tcp_client.o: tcp_client.h tcp_client.c
#	gcc -Wall -Wextra -c -g tcp_client.c

clean:
	rm -f etest
	rm -f *.o

run:
	./etest
