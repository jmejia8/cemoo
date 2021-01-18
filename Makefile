main: main.c
	gcc main.c -Ofast -lm -o main

run: main.c
	make && ./main

clean:
	rm main

test:
	gcc main.c -Wall -O0 -lm -o main && ./main
