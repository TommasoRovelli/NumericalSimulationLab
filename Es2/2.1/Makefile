CC = g++
CFLAGS = -Wall -O3 --std=c++11

2.1.exe: 2.1.o func.o random.o integral.o
	$(CC) func.o random.o integral.o 2.1.o -o 2.1.exe 

2.1.o: 2.1.cpp
	$(CC) -c 2.1.cpp -o 2.1.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

func.o: func.cpp func.h random.h 
	$(CC) -c func.cpp -o func.o $(CFLAGS)

integral.o: integral.cpp integral.h random.h
	$(CC) -c integral.cpp -o integral.o $(CFLAGS)

clean:
	rm *.o *.exe *.out