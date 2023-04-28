default: all
all: client server

TAR=tar
TARFLAGS=-cvf
TARNAME=345175475_207603846.tgz
TARSRCS=$(SRC) Makefile README Results.pdf server.cpp client.cpp



server: server.cpp
	g++ -Wall server.cpp -o server

client: client.cpp
	g++ -Wall client.cpp -o client

tar:
	$(TAR) $(TARFLAGS) $(TARNAME) $(TARSRCS)