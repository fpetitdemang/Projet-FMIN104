serveur: serveur.o sock.o sockdist.o
	g++ -o serveur serveur.o sock.o sokdist.o

serveur.o: serveur.cpp sock.h sockdist.h
	g++ -Wall -c serveur.cpp

sock.o: sock.cpp sock.h
	g++ -Wall -c sock.cc

sockdist.o: serveur.cpp sock.h sockdist.h
	g++ -Wall -c serveur.cc

#
# Cibles habituelles
#
clean :
rm −f ∗˜

mrproper : clean
rm −f serveur

−o serveur serveur.cpp
