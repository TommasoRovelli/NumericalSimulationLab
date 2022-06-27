CC = mpicxx
CFLAGS = -Wall -O3 --std=c++11

10.1.exe: 10.1.o TravellingSalesman.o Coordinates.o City.o Path.o random.o
	$(CC) 10.1.o TravellingSalesman.o City.o Coordinates.o Path.o random.o -o 10.1.exe

10.1.o: 10.1.cpp
	$(CC) -c 10.1.cpp -o 10.1.o $(CFLAGS)

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

clean:
	rm *.o *.exe *.out