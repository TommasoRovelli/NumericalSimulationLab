CC = g++
CFLAGS = -Wall -O3 --std=c++11

9.1.exe: 9.1.o TravellingSalesman.o Coordinates.o City.o Path.o random.o
	$(CC) 9.1.o TravellingSalesman.o City.o Coordinates.o Path.o random.o -o 9.1.exe

9.1.o: 9.1.cpp
	$(CC) -c 9.1.cpp -o 9.1.o $(CFLAGS)

TravellingSalesman.o: TravellingSalesman.cpp TravellingSalesman.h
	$(CC) -c TravellingSalesman.cpp -o TravellingSalesman.o $(CFLAGS)

City.o: City.cpp City.h 
	$(CC) -c City.cpp -o City.o $(CFLAGS)

Coordinates.o: Coordinates.cpp Coordinates.h
	$(CC) -c Coordinates.cpp -o Coordinates.o $(CFLAGS)

Path.o: Path.cpp Path.h 
	$(CC) -c Path.cpp -o Path.o $(CFLAGS)

random.o: random.cpp random.h 
	$(CC) -c random.cpp -o random.o $(CFLAGS)

circle.exe: circle.o random.o
	$(CC) circle.o random.o -o circle.exe 

circle.o: circle.cpp
	$(CC) -c circle.cpp -o circle.o $(CFLAGS)

square.exe: square.o random.o
	$(CC) square.o random.o -o square.exe 

square.o: square.cpp
	$(CC) -c square.cpp -o square.o $(CFLAGS)

clean:
	rm *.o *.exe *.out