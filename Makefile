SRCC=Analysis_of_Algorithms.tex
EXEC=$(SRCC:.tex=.pdf)
INCLUDES=.:./Homework//:
INCLUDES+=.:./Exam_Guides//:

all: compile view

compile: export TEXINPUTS=$(INCLUDES)
compile:
		pdflatex $(SRCC)

view:
		evince $(EXEC) &

clean:
		rm -f *.aux *.log *.pdf
