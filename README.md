# printf implementation (language: C)
The goal is to implement a custom printf function, called _printf, which can 
print variables in string format according to the directive of the format 
specifiers (%d, %c, %s etcetera).

## Milestones Achieved
- _printf function working as expected: Prints a string and uses the format
specifiers to interpret it into its appropriate string value by fetching the 
corresponding vaue from the variable arguments.

- replaced putchar() with write() completely

- _printf returns the number of characters printed

- placed functions into header file (main.h) and removed the main() function 
from _printf.c


## TODOs

- if required, reduce number of functions
 
- tuck global variables into functions


## HOW WE WILL DO THE TESTS:
- navigate to the directory "test" and run: gcc main.c ../_printf.c -o testrun
This creates an executable named "testrun" in the directory "test"

- run this executable using: ./testrun    to see the output.

