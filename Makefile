CC = gcc

CFLAGS  = -Wall -lm 

TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET)
	$(CC) $(TARGET).c $(CFLAGS) -Ofast -o $(TARGET).bin

clean:
	rm *.bin

test:
	$(CC) test_non_dominated.c $(CFLAGS) -O0 -o test.bin && ./test.bin txt/instances.txt


experiment:
	$(CC) test_non_dominated.c $(CFLAGS) -Ofast -o test.bin && ./test.bin txt/instances.txt

