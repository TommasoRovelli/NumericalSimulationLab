CC = g++
CFLAGS = -Wall -O3 --std=c++11

1.3.exe: 1.3.o func.o random.o buffon.o
	$(CC) func.o random.o buffon.o 1.3.o -o 1.3.exe 

1.3.o: 1.3.cpp
	$(CC) -c 1.3.cpp -o 1.3.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

func.o: func.cpp func.h random.h 
	$(CC) -c func.cpp -o func.o $(CFLAGS)

buffon.o: buffon.cpp buffon.h random.h
	$(CC) -c buffon.cpp -o buffon.o $(CFLAGS)

clean:
	rm *.o *.exe *.out