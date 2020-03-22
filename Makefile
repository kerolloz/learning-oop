CXXFLAGS = -Wall -std=gnu++17

create-exercise: create-exercise.o
	$(LINK.cpp) $^ $(LDLIBS) -o $@

create-exercise.o: exercise.hpp