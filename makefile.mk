CC = gcc -g
CFLASGS = -Wall -lncurses
SOURCE = $(wildcard *.c)
OBJETS = $(SOURCE:.c=.o)
EXEC = main
$(EXEC): $(OBJETS)
	$(CC) $(CFLASGS) -o $@ $^ -lm
%.o: %.c
	$(CC) $(CFLASGS) -c $<

clean:
	rm -f *.o
	rm -f $(EXEC)