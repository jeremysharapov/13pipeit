all: pip.c
	gcc pip.c -o pipe
run: all
	./pipe
clean:
	rm -f *~
	rm -f *.o
