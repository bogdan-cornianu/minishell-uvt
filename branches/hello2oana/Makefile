#
# Makefile Munteanu Oana
#

main:
	@echo "Use <make \"command\"> to compile the command"

all: echo chmod umask uname
	
clean:
	rm -f *.o
	@echo "All object files *.o removed"

# echo make
echo: echo.o
	gcc -o echo echo.o	
echo.o: echo.c
	gcc -c echo.c
##

# chmod make
chmod: chmod.o
	gcc -o chmod chmod.o
chmod.o: chmod.c
	gcc -c chmod.c
##

# umask
umask: umask.o
	gcc -o umask umask.o
umask.o: umask.c
	gcc -c umask.c
##

# uname
uname: uname.o
	gcc -o uname uname.o
uname.o: umask.c
	gcc -c uname.c
##