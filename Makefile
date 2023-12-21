CXX = g++-11 -std=c++20
CXXFLAGS = -Wall -g -MMD
SOURCES = $(wildcard *.cc)
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC=chess

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean 
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
