CXX := g++
CFLAGS := -g3 -std=c++11


PROGRAM := LO5R_MOCK_OUT
INCLUDE := ./include
SRC := ./src

OBJS := $(SRC)/*.cpp

$(PROGRAM) : clean $(OBJS)
	$(CXX) $(CFLAGS) -I$(INCLUDE)  $(OBJS) -o $(PROGRAM)

clean :
	rm -rf $(SRC)/*.o $(PROGRAM)

run : $(PROGRAM)
	./$(PROGRAM)

valgrind : $(PROGRAM)
	valgrind --leak-check=full --log-file=valgrind-out.txt ./$(PROGRAM)

