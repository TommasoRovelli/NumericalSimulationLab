CC = g++
CFLAGS = -Wall -O3 --std=c++11

1.1.exe: 1.1.o func.o random.o
	$(CC) func.o random.o 1.1.o -o 1.1.exe 

1.1.o: 1.1.cpp
	$(CC) -c 1.1.cpp -o 1.1.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

func.o: func.cpp func.h random.h 
	$(CC) -c func.cpp -o func.o $(CFLAGS)

clean:
	rm *.o *.exe *.out


