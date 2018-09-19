TARGET = proj1
GCC = gcc
CFLAGS = -g -Wall -Wshadow -Werror -O3 -lm
CC = $(GCC) $(CFLAGS)
SRCS = sorting.c sorting_main.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./proj1

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)


