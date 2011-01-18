all: fsmprog
	./fsmprog

fsmprog: Node.o FSA.o tester_pictures.o
	g++ -g -o fsmprog Node.o FSA.o tester_pictures.o

Node.o: Node.cpp
	g++ -c -g Node.cpp

FSA.o: FSA.cpp
	g++ -c -g FSA.cpp

tester_pictures.o: tester_pictures.cpp
	g++ -c -g tester_pictures.cpp

clean:
	rm *.o; rm fsmprog
