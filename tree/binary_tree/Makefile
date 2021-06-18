CC = gcc
CFLAGS =-Wall
DEPS = queue_ll.h stack_ll.h binary_tree.h
OBJS = main.o queue_ll.o stack_ll.o binary_tree.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS) 
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ core main
