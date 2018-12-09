# IMS project 2018 repka olejka

# author: Erik Kelemen
# author: Petr Kapoun


TARGET = IMS

CC=g++

CFLAGS=-O2 -Wall -pedantic -lm

MODULES= season land parser

OBJS = $(addprefix obj/, $(addsuffix .o,$(MODULES)))

DOC_FOLDER = docs

DOC_NAME = documentation


all: $(TARGET)
.PHONY: clean, dokumentace

$(TARGET) : $(OBJS) src/main.cc
	$(CC) $(CFLAGS) $(OBJS) src/main.cc src/simlib.a -o $@

obj/%.o : src/%.cc src/%.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f ./obj/*.o $(TARGET)
	rm -f ./$(DOC_FOLDER)/*.aux
	rm -f ./$(DOC_FOLDER)/*.dvi
	rm -f ./$(DOC_FOLDER)/*.ps
	rm -f ./$(DOC_FOLDER)/*.bbl
	rm -f ./$(DOC_FOLDER)/*.bbg
	rm -f ./$(DOC_FOLDER)/*.log
	rm -f ./$(DOC_FOLDER)/*.toc
	rm -f ./$(DOC_FOLDER)/*.blg
	rm -f ./$(DOC_FOLDER)/*.pdf
	rm -f ./$(DOC_FOLDER)/*.out

test:
	chmod +x test.sh
	./test.sh

documentation: $(DOC_FOLDER)/$(DOC_NAME).tex
	#cd $(DOC_FOLDER) && latex $(DOC_NAME).tex
	#cd $(DOC_FOLDER) && bibtex $(DOC_NAME).aux
	#cd $(DOC_FOLDER) && latex $(DOC_NAME).tex
	#cd $(DOC_FOLDER) && latex $(DOC_NAME).tex
	#cd $(DOC_FOLDER) && dvips -t a4 $(DOC_NAME).dvi
	#cd $(DOC_FOLDER) && ps2pdf $(DOC_NAME).ps
	cd $(DOC_FOLDER) && pdflatex $(DOC_NAME).tex
	cd $(DOC_FOLDER) && pdflatex $(DOC_NAME).tex
