CC= gcc
CFLAGS= -Wall -g

PRGS=lfsr a51 berlekamp

all: $(PRGS)

lfsr: test.o lfsr.o
	$(CC) lfsr.o test.o -o $@

a51: a51.o lfsr.o
	$(CC) lfsr.o a51.o -o $@
	
berlekamp: berlekamp.o lfsr.o
	$(CC) berlekamp.o lfsr.o -o $@
	
berlekamp.o: Berlekamp.c lfsr.h
	$(CC) $(CFLAGS) -c Berlekamp.c -o $@

lfsr.o: lfsr.c
	$(CC) $(CFLAGS) -c lfsr.c -o lfsr.o 

test.o: test.c lfsr.h
	$(CC) $(CFLAGS) -c test.c -o $@

a51.o: a51.c
	$(CC) $(CFLAGS) -c a51.c -o $@	

clean:
	find . -name '*.o' -exec rm -f {} ';'
	find . -name '*.a' -exec rm -f {} ';'
	find . -name '*.so' -exec rm -f {} ';'
	find . -name '*~' -exec rm -f {} ';'
	find . -name '#*#' -exec rm -f {} ';'
	find . -name '.#*' -exec rm -f {} ';'
	find . -name 'core' -exec rm -f {} ';'
	find . -name '*.core' -exec rm -f {} ';'
	
mrproprer: clean
	-rm -rf $(PRGS)
	
