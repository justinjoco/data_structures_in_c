TARGET = proj5
GCC = gcc
CFLAGS = -g -Wall -Wshadow -Werror -O3
CC = $(GCC) $(CFLAGS)
SRCS = genome.c genome_main.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./proj5

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)


