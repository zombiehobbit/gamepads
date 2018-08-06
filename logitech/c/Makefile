# make file edited

#etest: main.o logitech.o
#	g++ -o etest main.o logitech.o
etest: main.o gamepad.o
	g++ -o etest main.o gamepad.o


#main.o: main.c logitech.h
#	gcc -Wall -Wextra -c main.c

main.o: main.c gamepad.h
	gcc -Wall -Wextra -c main.c

#logitech.o: logitech.c logitech.h
#	gcc -Wall -Wextra -c logitech.c

gamepad.o: gamepad.c gamepad.h
	gcc -Wall -Wextra -c gamepad.c

# NOTE: for some reason this isn't loading
# UPDATE: I think it's working now
# build rules for the tcp_client
tcp_client.o: tcp_client.h tcp_client.c
	gcc -Wall -Wextra -c tcp_client.c

clean:
	rm -f etest
	rm -f *.o

run:
	./etest
