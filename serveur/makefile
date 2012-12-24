all: obs.o sock.o objet.o #sauvegarde.o
	g++ `pkg-config --cflags --libs gtk+-2.0`  *.o -o serveur -lpthread 

sock.o: ../Sock/sock.cc ../Sock/sockdist.cc 
	g++ -c -g ../Sock/sock.cc ../Sock/sockdist.cc

obs.o: ../Observer/Subject.cpp ../Observer/Observer.cpp 
	g++ -c -g ../Observer/Subject.cpp ../Observer/Observer.cpp 

objet.o: *.cpp *.h
	g++ -c -g *.cpp

#sauvegarde.o: fournisSujet1/sauvegarde.c
#	g++  `pkg-config --cflags --libs gtk+-2.0` -c -g  fournisSujet1/sauvegarde.c  

clean:
	rm *.o
