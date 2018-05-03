# cxx=g++
# cxx=g++ -fopenmp
# cxx=g++-7
# cxx=g++-7 -fopenmp
cxx=mpic++
# cxx=mpic++ -fopenmp
cflags+=-std=c++11

execs=run

objs=\
	board.cpp \
	board_deque.cpp \
	solver.cpp \
	bootstrapper.cpp \
	sudoku.cpp \
	sudoku_mpi.cpp \
	sudoku_mpi_static.cpp \
	sudoku_mpi_dynamic.cpp \
	# sudoku_serial.cpp \
	# sudoku_queue_scheme.cpp \

src=$(patsubst %.cpp,$(objs))

all: $(execs)

clean:
	rm $(objs) $(execs)

run: main.cpp $(objs)
	$(cxx) $(cflags) -o $@ $^

.PHONY: clean depend
