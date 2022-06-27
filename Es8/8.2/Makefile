CC = g++
CFLAGS = -Wall -O3 --std=c++11

8.2.exe: prova.o 8.2.o random.o integral.o integral.cpp
	$(CC) random.o integral.o 8.2.o -o 8.2.exe 

8.2.o: 8.2.cpp
	$(CC) -c 8.2.cpp -o 8.2.o $(CFLAGS)

prova.exe: prova.o random.o integral.o
	$(CC) random.o integral.o prova.o -o prova.exe

prova.o: prova.cpp
	$(CC) -c prova.cpp -o prova.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

integral.o: integral.cpp integral.h random.h
	$(CC) -c integral.cpp -o integral.o $(CFLAGS)

clean:
	rm *.o *.exe *.out