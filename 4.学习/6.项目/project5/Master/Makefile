CC = gcc

SHDIR = ../common

CFLAGS = -Wall -lpthread -lm -I ${SHDIR}


OBJS = master.o $(SHDIR)/common.o

all : master
	@echo "Finsh!"


pihealthd: $(OBJS)
	echo @$(CC) -o $@ $(CFLAGS) $(OBJS)

$(OBJS): %.o : %.c
	$(CC) -c $(CFLAGS) $<


.PHONY: clean

clean:
	@rm -f *.o master
	@rm -f $(SHDIR)/common.o
	@echo "Clean Done"




install:
	
