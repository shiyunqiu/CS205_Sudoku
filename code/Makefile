# Include the configuration file
include config.mk

cflags+=-std=c++11

# Lists of files to be built
objs=sudoku.o sudoku_serial.o sudoku_parallel.o
src=$(patsubst %.o,%.cpp,$(objs))
execs=sudoku_run

all: $(execs)

# Include the file dependencies
-include Makefile.dep

# A Makefile target to refresh the dependency file
depend:
	$(cxx) $(iflags) -MM $(src) >Makefile.dep

# A Makefile target to remove all the built files
clean:
	rm $(objs) $(execs)

%.o: %.cpp
	$(cxx) $(cflags) $(iflags) -c $<

sudoku_run: main.cpp $(objs)
	$(cxx) $(cflags) -o $@ $^

# sudoku_run: sudoku_run.cc $(objs)
# 	$(cxx) $(cflags) -o $@ $^

# sudoku_print: sudoku_print.cc $(objs)
# 	$(cxx) $(cflags) -o $@ $^

# sudoku_timings: sudoku_timings.cc $(objs)
# 	$(cxx) $(cflags) -o $@ $^

# sudoku_chris: sudoku_chris.cc $(objs)
# 	$(cxx) $(cflags) -o $@ $^

.PHONY: clean depend
