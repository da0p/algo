CC = gcc
CFLAGS =-Wall
DEPS = queue_ll.h stack_ll.h bst.h
OBJS = main.o queue_ll.o stack_ll.o bst.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS) 
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ core main
