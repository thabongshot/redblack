.SUFFIXES : .c .o
CC = gcc
CFLAGS = -g -Wall -ansi
 all: test

OBJS = rbtree.o main.o
SRCS = $(OBJS:.o=.c)

test: $(OBJS)
	$(CC) -o rbtree $(OBJS) 

clean: 
	rm -rf $(OBJS)
distclean: 
	rm -rf $(OBJS) rbtree
