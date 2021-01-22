# Code on Evolutionary Multi-objective Optimization


Download this code via git clone or via the green button.


## Dominated Solutions

To find the non-dominated solutions from a given set.

Compile using `make` or `gcc main.c -Wall -lm  -Ofast -o main.bin` 
The binary program require two parameters, the file with the solutions and
the method to find non-dominated solutions.

Input data:

- TXT file separated by spaces.
- Method to use (1, 2 or 3).
 - `1` Simple method.
 - `2` Continuous update.
 - `3` Algorithm M3 (Bentley, 1993).

### Example

Create TXT file where the first line include the number of solutions and the number of
function separated by a space. The following lines are the solutions by rows.

Example: Ten solutions, three objective functions stored in `points.txt`.

```
10 3
4 2 3
3 2 5
1 5 4
2 3 0
1 3 8
6 0 1
8 2 2
3 1 5
4 4 5
9 1 1
```

Run using the command (after compilation): `./main.bin points.txt 2` to find the non-dominated
set with method 2.


Output:

```
Method = 2
non dominated = 6
time: 0.000003

1 3 4 5 6 8 
```

## Run experiments

To run the experiments, use the `make experiment` command.

Output:


```
+--------------------------------+
Method: 1	instance: txt/example1.txt	# non dominated: 6	time: 0.000004
Method: 2	instance: txt/example1.txt	# non dominated: 6	time: 0.000002
Method: 3	instance: txt/example1.txt	# non dominated: 6	time: 0.000002
+--------------------------------+
Method: 1	instance: txt/example2.txt	# non dominated: 8	time: 0.000003
Method: 2	instance: txt/example2.txt	# non dominated: 8	time: 0.000001
Method: 3	instance: txt/example2.txt	# non dominated: 8	time: 0.000002
+--------------------------------+
Method: 1	instance: txt/example_3000_3.txt	# non dominated: 34	time: 0.004199
Method: 2	instance: txt/example_3000_3.txt	# non dominated: 34	time: 0.000218
Method: 3	instance: txt/example_3000_3.txt	# non dominated: 34	time: 0.000142
+--------------------------------+
Method: 1	instance: txt/example_3000_4.txt	# non dominated: 103	time: 0.011851
Method: 2	instance: txt/example_3000_4.txt	# non dominated: 103	time: 0.000811
Method: 3	instance: txt/example_3000_4.txt	# non dominated: 103	time: 0.000492
+--------------------------------+
Method: 1	instance: txt/example_3000_5.txt	# non dominated: 240	time: 0.022198
Method: 2	instance: txt/example_3000_5.txt	# non dominated: 240	time: 0.002138
Method: 3	instance: txt/example_3000_5.txt	# non dominated: 240	time: 0.001468

All test passed. :D
```

## Development

To run the test in development mode, use the `make test` command.


