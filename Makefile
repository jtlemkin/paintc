paint.out: main.o canvas.o command.o draw.o inputValidation.o
	gcc -g -Wall -Werror -o paint.out main.o canvas.o command.o draw.o inputValidation.o

main.o: main.c canvas.h command.h
	gcc -g -Wall -Werror -c main.c

canvas.o: canvas.c canvas.h
	gcc -g -Wall -Werror -c canvas.c

command.o: command.c command.h draw.h inputValidation.h
	gcc -g -Wall -Werror -c command.c

draw.o: draw.c draw.h canvas.h
	gcc -g -Wall -Werror -c draw.c

inputValidation.o: inputValidation.c inputValidation.h command.h
	gcc -g -Wall -Werror -c inputValidation.c

clean:
	Rm -fr *.o *.out