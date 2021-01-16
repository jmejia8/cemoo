main: main.c
	gcc main.c -Ofast -o main

clean:
	rm main

test:
	gcc main.c -Wall -O0 -o main && ./main
