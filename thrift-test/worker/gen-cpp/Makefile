
CC=g++ -g -Wall

CFLAGS = -I. -I/usr/local/include/thrift 

LFLAGS = -L/usr/local/lib

LDEXEFLAGS = -lthrift 

OBJS = WorkerManager.o \
       worker_types.o \
       worker_constants.o 

all:client server


WorkerManager.o: WorkerManager.cpp
	$(CC) $(CFLAGS) -c -o $@
worker_types.o: worker_types.cpp
	$(CC) $(CFLAGS) -c -o $@
worker_constants.o: worker_constants.cpp
	$(CC) $(CFLAGS) -c -o $@
WorkerManager_server.skeleton.o: WorkerManager_server.skeleton.cpp
	$(CC) $(CFLAGS) -c -o $@
Client.o: Client.cpp
	$(CC) $(CFLAGS) -c -o $@

server: $(OBJS) WorkerManager_server.skeleton.o
	$(CC) $(LFLAGS) $(OBJS) WorkerManager_server.skeleton.o  $(LDEXEFLAGS) -o $@

client: $(OBJS)  Client.o
	$(CC) $(LFLAGS) $(OBJS)  Client.o  $(LDEXEFLAGS) -o $@


clean:
	rm -f ./*.o client server
