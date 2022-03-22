TC_FOLDER = tests
EXT_IN = in
EXT_OUT = out
EXT_ANS = ans
EXECUTABLE_FILENAME = main
ALL_SRCS := $(wildcard *.cpp)
SRCS     := $(filter-out check.cpp, $(ALL_SRCS))

all: compile test check

# Compile all cpp files except check.cpp
compile:
	g++ ./src/implementation/baseException.cpp ./src/implementation/craft.cpp \
	./src/implementation/inventory.cpp ./src/implementation/item.cpp ./src/implementation/itemConfig.cpp \
	./src/implementation/recipes.cpp ./src/implementation/move.cpp -std=c++17 -o $(EXECUTABLE_FILENAME) $(SRCS)

# Test
test: $(TC_FOLDER)/*.$(EXT_IN) $(EXECUTABLE_FILENAME)
	for inputfile in $(TC_FOLDER)/*.$(EXT_IN); do \
		./$(EXECUTABLE_FILENAME) < $$inputfile; \
	done;

# Check
check: FORCE check.cpp
	g++ -std=c++17 -o check check.cpp
	./check

FORCE: ;
