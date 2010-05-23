#
# Makefile Munteanu Oana
#

main:
	@echo "Use <make \"command\"> to compile the command"
	
clean:
	rm -f *.o
	@echo "All object files *.o removed"

# chmod
chmod: chmod.o
	gcc -o chmod chmod.o
chmod.o: chmod.c
	gcc -c chmod.c
##

# echo
echo: echo.o
	gcc -o echo echo.o	
echo.o: echo.c
	gcc -c echo.c
##

# sort
sort: sort.o
	gcc -o sort sort.o
sort.o: sort.c
	gcc -c sort.c
##

# time
time: time.o
	gcc -o time time.o
time.o: time.c
	gcc -c time.c
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

# whatis
whatis: whatis.o
	gcc -o whatis whatis.o
whatis.o: whatis.c
	gcc -c whatis.c
##
