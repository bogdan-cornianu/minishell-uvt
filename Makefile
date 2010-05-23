#
# Makefile Minica Patricia
#

main:
	@echo "Use <make \"command\"> to compile the command"

clean:
	rm -f *.o
	@echo "All object files *.o removed"

# apropos
apropos: apropos.o
	gcc -o apropos apropos.o
apropos.o: apropos.c
	gcc -c apropos.c
##
	
# clear
clear: clear.o
	gcc -o clear clear.o
clear.o: clear.c
	gcc -c clear.c
##
	
# date
date: date.o
	gcc -o date date.o
date.o: date.c
	gcc -c date.c
##

# gzip
gzip: gzip.o
	gcc -lz -o gzip gzip.o
gzip.o: gzip.c
	gcc -c gzip.c
##

# ls
ls: ls.o
	gcc -o ls ls.o
ls.o: ls.c
	gcc -c ls.c
##

# mkdir
mkdir: mkdir.o
	gcc -o mkdir mkdir.o
mkdir.o: mkdir.c
	gcc -c mkdir.c
##

# sleep make
sleep: sleep.o
	gcc -o sleep sleep.o
sleep.o: sleep.c
	gcc -c sleep.c
##
