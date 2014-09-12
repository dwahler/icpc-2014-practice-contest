EXECUTABLES=multiplication up-and-down coins ping scheduling

CPPFLAGS=-std=c++11 -O3

all: $(EXECUTABLES)

clean:
	rm -f $(EXECUTABLES)
