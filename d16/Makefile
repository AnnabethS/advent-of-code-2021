one: hexUtils.o
	clang one.c hexUtils.o

oneT: hexUtils.o
	clang one.c hexUtils.o -D TEST

two: hexUtils.o
	clang two.c hexUtils.o

twoT: hexUtils.o
	clang two.c hexUtils.o -D TEST

hexUtils.o: hexUtils.c
	clang -c hexUtils.c -o hexUtils.o

clean:
	rm a.out
