all: controleur.o sock.o sockdist.o
	g++ sock.o sockdist.o controleur.o -o controleur

controleur.o: controleur.cpp
	g++ -c controleur.cpp	

sock.o: ../Sock/sock.cc ../Sock/sock.h
	g++ -Wall -c ../Sock/sock.cc

sockdist.o: ../Sock/sockdist.cc ../Sock/sockdist.h
	g++ -Wall -c ../Sock/sockdist.cc


clean:
	rm *.o