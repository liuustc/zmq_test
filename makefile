INCLUDE=./include
CMP=g++

all: zmq_sender zmq_recv
zmq_sender: send.o
	$(CMP) send.o -lzmq -o zmq_sender
send.o: send.cc
	$(CMP) -c send.cc -lzmq

zmq_recv: recv.o
	$(CMP) recv.o -lzmq -o zmq_recv
recv.o: recv.cc
	$(CMP) -c recv.cc -lzmq

