CXX = g++
CXXFLAGS += -g -Wall -Wextra -Werror

SRCS = biblioteca.cpp main.cpp
HEADERS = $(wildcard *.h)

main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -U_FORTIFY_SOURCE -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug
