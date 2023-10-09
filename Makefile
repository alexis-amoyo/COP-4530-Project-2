CC := g++

CFLAGS := -std=c++11 

SRCS := measure_reverse.cpp test_list.cpp measure.cpp

OBJS := ${SRCS:.cpp=.o} measure.o measure_reverse.o test_list.o

PROGS := ${SRCS:.cpp=}

.PHONY: all
all: ${PROGS}

test_list: test_list.o
	${CC} ${CFLAGS} -o $@ $^
	
measure: measure.o
	${CC} ${CFLAGS} -o $@ $^

measure_reverse: measure_reverse.o
	${CC} ${CFLAGS} -o $@ $^

%.o: %.cpp
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${PROGS} ${OBJS} *.bak *~
