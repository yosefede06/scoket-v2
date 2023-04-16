default: all
all: client server

#TAR=tar
#TARFLAGS=-cvf
#TARNAME=ex5.tar
#TARSRCS=$(SRC) Makefile README server.cpp client.cpp



server: server.cpp
	g++ -Wall server.cpp -o server

client: client.cpp
	g++ -Wall client.cpp -o client




clean:
	$(RM) $(TARGETS) *~ *core
tar:
	$(TAR) $(TARFLAGS) $(TARNAME) $(TARSRCS)