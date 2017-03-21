prog_ex10: Aula03_ex09.o num_caracs.o
	gcc $(CFLAGS) -o prog_ex10 Aula03_ex09.o num_caracs.o
Aula03_ex09.o: Aula03_ex09.c num_caracs.h
	gcc $(CFLAGS) -c Aula03_ex09.c
num_caracs.o: num_caracs.c num_caracs.h
	gcc $(CFLAGS) -c num_caracs.c
clean:
	rm -f *.o prog_ex10
