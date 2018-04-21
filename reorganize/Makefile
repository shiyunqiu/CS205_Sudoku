cxx=g++-7
# cxx=g++-7 -fopenmp
# cxx=mpic++ -openmp
cflags+=-std=c++11

execs=run
objs=\
	board.cpp \
	board_container.h \
	board_queue.cpp \
	solver.cpp \
	bootstrapper.cpp \
	board_stack.cpp
src=$(patsubst %.o,%.cpp,$(objs))

all: $(execs)

clean:
	rm $(objs) $(execs)

run: main.cpp $(objs)
	$(cxx) $(cflags) -o $@ $^

.PHONY: clean depend
