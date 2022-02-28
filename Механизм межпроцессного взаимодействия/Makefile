programs = fileserver fileclient
all: ${programs} 

fileserver: fileserver_main.o fileserver_func.o fileserver_func_2.o
	gcc fileserver_main.o fileserver_func.o fileserver_func_2.o -o fileserver

fileserver_main.o: fileserver_main.c
	gcc fileserver_main.c -c -o fileserver_main.o

fileserver_func.o: fileserver_func.c
	gcc fileserver_func.c -c -o fileserver_func.o

fileserver_func_2.o: fileserver_func_2.c
	gcc fileserver_func_2.c -c -o fileserver_func_2.o
fileserver.o: fileserver.c
	gcc fileserver.c -c -o fileserver.o

fileclient: fileclient_main.o fileclient_func.o
	gcc fileclient_main.o fileclient_func.o -o fileclient

fileclient_main.o: fileclient_main.c
	gcc fileclient_main.c -c -o fileclient_main.o 

fileclient_func.o: fileclient_func.c
	gcc fileclient_func.c -c -o fileclient_func.o

clean: 
	rm -rf *.o ${programs}