# IMS project 2018 repka olejka

# author: Erik Kelemen


TARGET = IMS

CC=g++

CFLAGS=-O2 -Wall -pedantic

MODULES=

OBJS = $(addprefix obj/, $(addsuffix .o,$(MODULES)))



all: $(TARGET)
.PHONY: clean, dokumentace

$(TARGET) : $(OBJS) src/main.cc
	$(CC) $(CFLAGS) $(OBJS) src/main.cc simlib.a -o $@

obj/%.o : src/%.cc src/%.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f ./obj/*.o $(TARGET)

test:
	chmod +x test.sh
	./test.sh

documentation: docs/documentation.tex
	cd docs && pdflatex documentation.tex
