CC = gcc
CFLAGS =-Wall
DEPS = queue_ll.h twothree_tree.h
OBJS = main.o queue_ll.o twothree_tree.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS) 
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ core main
