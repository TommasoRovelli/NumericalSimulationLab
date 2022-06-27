CC = g++
CFLAGS = -Wall -O3 --std=c++11

2.2.exe: 2.2.o func.o random.o randomwalk.o
	$(CC) func.o random.o randomwalk.o 2.2.o -o 2.2.exe 

2.2.o: 2.2.cpp
	$(CC) -c 2.2.cpp -o 2.2.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

func.o: func.cpp func.h random.h 
	$(CC) -c func.cpp -o func.o $(CFLAGS)

randomwalk.o: randomwalk.cpp randomwalk.h random.h
	$(CC) -c randomwalk.cpp -o randomwalk.o $(CFLAGS)

clean:
	rm *.o *.exe *.out