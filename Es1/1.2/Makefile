CC = g++
CFLAGS = -Wall -O3 --std=c++11

1.2.exe: 1.2.o func.o random.o
	$(CC) func.o random.o 1.2.o -o 1.2.exe 

1.2.o: 1.2.cpp
	$(CC) -c 1.2.cpp -o 1.2.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

func.o: func.cpp func.h random.h 
	$(CC) -c func.cpp -o func.o $(CFLAGS)

clean:
	rm *.o *.exe *.out