INCLUDE=./include
CMP=g++

all: zmq_sender zmq_recv
zmq_sender: send.o
	$(CMP) send.o -L. -lzmq -o zmq_sender
send.o: send.cc
	$(CMP) -c send.cc -lzmq -I.

zmq_recv: recv.o
	$(CMP) recv.o -L. -lzmq -o zmq_recv
recv.o: recv.cc
	$(CMP) -c recv.cc -lzmq -I.

clean:
	rm recv.o send.o
