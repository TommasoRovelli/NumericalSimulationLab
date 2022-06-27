CC = g++
CFLAGS = -Wall -O3 --std=c++11

3.1.exe: 3.1.o func.o random.o blackscholes.o
	$(CC) func.o random.o blackscholes.o 3.1.o -o 3.1.exe 

3.1.o: 3.1.cpp
	$(CC) -c 3.1.cpp -o 3.1.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

func.o: func.cpp func.h random.h 
	$(CC) -c func.cpp -o func.o $(CFLAGS)

blackscholes.o: blackscholes.cpp blackscholes.h random.h
	$(CC) -c blackscholes.cpp -o blackscholes.o $(CFLAGS)

clean:
	rm *.o *.exe *.out