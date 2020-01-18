part1: part1.o
	gcc part1.o -o part1.out -lpthread

part1.o: part1.c
	gcc -c part1.c -lpthread

part2: part2.o
	gcc part2.o -o part2.out

part2.o: part2.c
	gcc -c part2.c 


clean:
	rm -f cpu_scheduling_output_file.txt *.out *.o core
