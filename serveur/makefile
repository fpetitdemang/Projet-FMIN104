all : obs.o sock.o objet.o
	g++  *.o -o serveur -lpthread


sock.o : ../Sock/sock.cc ../Sock/sockdist.cc 
	g++ -c -g ../Sock/sock.cc ../Sock/sockdist.cc

obs.o : ../Observer/Subject.cpp ../Observer/Observer.cpp 
	g++ -c -g ../Observer/Subject.cpp ../Observer/Observer.cpp 

objet.o : *.cpp *.h
	g++ -c -g *.cpp

clean:
	rm ∗.o