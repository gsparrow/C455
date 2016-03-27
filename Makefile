SRCC=Analysis_of_Algorithms.tex
EXEC=$(SRCC:.tex=.pdf)

all: compile view

compile:
		 pdflatex $(SRCC)

view:
		 evince $(EXEC) &

clean:
		rm -f *.aux *.log *.pdf
