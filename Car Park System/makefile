CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY: all
all: vehicle

vehicle : mainCarPark.cpp carParkFunction.o
	$(CXX) $(CXXFLAGS) -o $@ $^
carParkFunction.o : carParkFunction.cpp parking.h
	$(CXX) $(CXXFLAGS) -c $<
.PHONY: clean
clean:
	rm *~ *.o vehicle
