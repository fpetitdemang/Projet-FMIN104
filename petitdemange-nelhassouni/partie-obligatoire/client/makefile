client: client.o sock.o sockdist.o
	g++ -o client client.o sock.o sockdist.o
 
client.o: client.cpp ../Sock/sock.h ../Sock/sockdist.h
	g++ -Wall -c client.cpp


sock.o: ../Sock/sock.cc ../Sock/sock.h
	g++ -Wall -c ../Sock/sock.cc

sockdist.o: ../Sock/sockdist.cc ../Sock/sockdist.h
	g++ -Wall -c ../Sock/sockdist.cc



#
# Cibles habituelles
#
clean:
	rm *.o