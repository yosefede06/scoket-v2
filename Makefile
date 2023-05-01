# List of source files
SRC = server.cpp client.cpp

# Name of the tarball file
TARNAME = 345175475_207603846.tgz

# Tar command
TAR = tar
TARFLAGS = -cvf

# Targets
.PHONY: all clean tar

# Default target
default: all

# Target to build everything
all: client server

# Target to build the server
server: server.cpp
	g++ -Wall -o server server.cpp

# Target to build the client
client: client.cpp
	g++ -Wall -o client client.cpp

# Target to create a tarball of the source files
tar:
	$(TAR) $(TARFLAGS) $(TARNAME) $(SRC) Makefile README Results.pdf MACROS.h

# Target to clean up object files and executables
clean:
	rm -f server client *.o $(TARNAME)
