cxx=g++ -fopenmp
# cxx=g++-7
# cxx=g++-7 -fopenmp
# cxx=mpic++
# cxx=mpic++ -openmp
cflags+=-std=c++11

execs=run

objs=\
	board.cpp \
	board_deque.cpp \
	solver.cpp \
	bootstrapper.cpp \
	sudoku.cpp \
	sudoku_serial.cpp \
	sudoku_queue_scheme.cpp \
	# sudoku_mpi.cpp \

src=$(patsubst %.cpp,$(objs))

all: $(execs)

clean:
	rm $(objs) $(execs)

run: main.cpp $(objs)
	$(cxx) $(cflags) -o $@ $^

.PHONY: clean depend
