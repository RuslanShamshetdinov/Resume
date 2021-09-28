all: tt5

tt5: main.o  help.o match_information.o
	g++ main.o help.o match_information.o -o tt5
main.o: main.cpp
	g++ main.cpp -c -o main.o

help.o: help.cpp 
	g++ help.cpp -c -o help.o

match_information.o: match_information.cpp
	g++ match_information.cpp -c -o match_information.o
clean:
	rm -rf *.o tt5
