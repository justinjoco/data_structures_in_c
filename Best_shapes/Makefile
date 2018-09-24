TARGET = proj4
GCC = gcc
CFLAGS = -g -Wall -Wshadow -Werror -O3
CC = $(GCC) $(CFLAGS)
SRCS = packing.c reroot_main.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./proj4

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)


