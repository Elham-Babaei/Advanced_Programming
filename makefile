EXE = main.x
CXX = g++
CXXFLAGS = -I src -g -std=c++17 -Wall -Wextra

SRC= main.cpp
OBJ=$(SRC:.cpp=.o)
INC = src/bst.hpp  src/node.hpp  src/iterator.hpp

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .o

all: $(EXE)

.PHONY: all

clean:
	rm -rf $(OBJ) $(EXE) src/*~ *~ html latex

.PHONY: clean

# %.o: %.cpp ap_error.h
# 	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

documentation: Doxygen/doxy.in
	doxygen $^

.PHONY: documentation

binary_search_tree.o: src/node.hpp src/bst.hpp src/iterator.hpp

format: $(SRC) $(INC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this commands"

.PHONY: format
