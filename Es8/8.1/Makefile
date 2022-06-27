CC = g++
CFLAGS = -Wall -O3 --std=c++11

8.1.exe: 8.1.o random.o integral.o
	$(CC) random.o integral.o 8.1.o -o 8.1.exe 

8.1.o: 8.1.cpp
	$(CC) -c 8.1.cpp -o 8.1.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

integral.o: integral.cpp integral.h random.h
	$(CC) -c integral.cpp -o integral.o $(CFLAGS)

clean:
	rm *.o *.exe *.out