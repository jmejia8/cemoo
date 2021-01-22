CC = gcc

CFLAGS  = -Wall -lm 

TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET)
	$(CC) $(TARGET).c $(CFLAGS) -Ofast -o $(TARGET).run

run: main.c
	make && ./main

clean:
	rm *.run

test:
	$(CC) test_non_dominated.c $(CFLAGS) -O0 -o test.run && ./test.run txt/instances.txt


experiment:
	$(CC) test_non_dominated.c $(CFLAGS) -Ofast -o test.run && ./test.run txt/instances.txt

