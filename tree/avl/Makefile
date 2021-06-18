CC = gcc
CFLAGS =-Wall
DEPS = 
OBJS = avl.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS) 
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ core main
