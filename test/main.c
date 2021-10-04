// This is where our tests will be carried out, thus the main() function will 
// be placed here and not in _printf.c. This is because ALX will use their
// automatic checker to place their own main file (containing a main() ) in the
// root folder of the project.

// Just note: ALX will not see this directory, so we can play around here. Only
// the contents of the root directory matters to the automatic checker.

// --------------------------------------------------------------
// HOW WE WILL DO THE TESTS:
// - navigate to the directory "test" and run: gcc main.c ../_printf.c -o testrun
// this creates an executable named "testrun" in the directory "test"
// run this executable using: ./testrun    to see the output.
// ---------------------------------------------------------------

// go to previous (..) directory (project root directory) and include main.h
#include "../main.h"


int main(void)
{
    // _printf("Option %c: In %d years, %d citizens will migrate from %s",option, years, migrants, country);
    // option:     'B'      (char)
    // years:       3       (int)
    // migrants:    781     (int)
    // country:     "Florida" (string)
    // expected output: Option B: In 3 years, 781 citizens will migrate from Florida

    char option = 'B';
    int years = 3;
    int migrants = 781;
    char *country = "Florida";
    _printf("Option %c: In %d years, %d citizens will migrate from %s\n",option, years, migrants, country);
    _printf("%");
}