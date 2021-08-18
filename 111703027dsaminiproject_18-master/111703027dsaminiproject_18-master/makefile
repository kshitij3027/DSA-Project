all : project
project: sort.o main.o
	gcc project.o sort.o -o project
sort.o: sort.c sort.h
	gcc -c sort.c
project.o: project.c sort.h
	gcc -c project.c	
