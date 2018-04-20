# cxx=g++-7 -fopenmp
cxx=g++-7
cflags+=-std=c++11

execs=sudoku_run
objs=Sudoku.cpp Sudoku_serial.cpp Sudoku_parallel.cpp
src=$(patsubst %.o,%.cpp,$(objs))

all: $(execs)

clean:
	rm $(objs) $(execs)

sudoku_run: main.cpp $(objs)
	$(cxx) $(cflags) -o $@ $^

.PHONY: clean depend
