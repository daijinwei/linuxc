CC      = g++
DEBUG 	= -g                      \
CFLAG 	= $(DEBUG)  -Wall -O2
CFLAG_DEBUG = $(DEBUG)  -Wall -O0

INC     = -I. -I../lib/c-ares-build/include
LIB     = -lrt  ../lib/c-ares-build/lib/libcares.a -lpthread 

BIN		= test
default:$(BIN)

OO		= main.o
$(BIN):$(OO)
	$(CC) -o $@ $(OO) $(LIB) $(CFLAG)
$(OO):%.o:%.cpp
	@echo "Compiling $@ <== $< ..."
	$(CC) -c -o $@ $< $(INC) $(CFLAG)

clean:
	-rm -f *.o $(BIN)
