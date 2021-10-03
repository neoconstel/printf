#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>


char alternate_special_chars[] = {'%','c','d','e','f','g','i','o','s','u','x','\0'};

// we're aiming for something like this below for _printf:
// _printf("Option %c: In %d years, %d citizens will migrate from %s",option, years, migrants, country);
// option:     'B'      (char)
// years:       3       (int)
// migrants:    781     (int)
// country:     "Florida" (string)
// output: Option B: In 3 years, 781 citizens will migrate from Florida
// ------------------------------------------------------

// function to return true if the character c is in the string else false
bool isin(char *string, const char c)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (c == string[i++])
            return true;
    }
    return false;      
}


// function to return number of valid formatters in a string
int count_valid_formatters(const char *string, ...)
{    
    // these are valid:
    //      "The child of %d years went to school"  
    //      "The girl named %   s was sent from the class" (white space does not terminate the open '%)

    // But this is not valid:
    //      "The girl named % z  s was sent from the class" (any character not in our list of alternate special characters terminates the open '%)

    int format_specifiers = 0;
    bool format_flag = false;   //true if % is 'open', and closed by any matching character from the alternate special characters list. E.g %c, %d or %%
    int i = 0;

    while (string[i] != '\0') // while we aren't yet at the end of the string
    {
        // if the current character is not a space and is not in our list of alternate special characters
        if (string[i] !=' ' && !(isin(alternate_special_chars, string[i]) ) ){
            format_flag = false;
        }            

        // else if current character is '%' and the format flag is false
        else if ( string[i] == '%' && format_flag == false )
        {
            format_flag = true;
        }
        
        // else if current character is in our list of alternate special characters and the format flag is true
        else if ( isin(alternate_special_chars, string[i]) && format_flag == true )
        {
            format_specifiers++;
            format_flag = false;
        }

        else
            ; // do nothing
        
        i++;  // increment i for checking the next index (position) in the string
    }    

    return format_specifiers;
}


int printnum_as_chars(long n){
    
    bool is_negative;

    // something to store the number length
    int characters_printed = 0;

    //ensure we are working with the absolute value of the number
    is_negative = n < 0? true:false;
    if (is_negative)
        n *= -1;
    
    // get divisor
    unsigned long divisor = 1;
    while(n >= divisor * 10){
        divisor *= 10;
        // characters_printed++;
    }
    
    //divisor_10 = divisor * 10
    unsigned long divisor_10 = divisor * 10;
    
    // print '-' sign if the number (before it was converted to absolute form) is negative
    if (is_negative) {
        putchar('-');
        characters_printed++;
    }

    // get/print digits, starting from highest value(4)
    int digit;
    int i = 0; //for storing the character form of the digit at index position of the buffer    
    do{
        digit = (n % divisor_10 - n % divisor) / divisor;            
        // print character equivalent of digit
        putchar('0' + digit);
        characters_printed++;
           
        divisor /= 10;
        divisor_10 /= 10;
    }while(divisor >= 1);           
    
    return characters_printed;
}



int _printf(const char *string, ...)
{
    // first count how many VALID format specifiers (how many valid opening '%' are closed with an alternate special charater )
    // so we can use it to initialize the argument pointer later on (via va_start)
    int n_specifiers = count_valid_formatters(string);


    /*Next steps: tap into the variable arguments and alternate between the format
    specifiers in the first(string) argument and the corresponding variables
    in the variable arguments. Return the corresponding type from va_arg 
    according to the corresponding format specifier. Append the interpreted forms
    of the variable in each case into a single string OR (as is being currently
    implemented) -- print directly*/

    va_list arg_ptr; // create a pointer to the variable arguments
    va_start(arg_ptr, n_specifiers); // initialize arg_ptr with the number of valid formatters in the string

    // using this as a guide:
    // _printf("Option %c: In %d years, %d citizens will migrate from %s",option, years, migrants, country);
    // output: Option B: In 3 years, 781 citizens will migrate from Florida

    // how printf behaves:
    // "stuff%         otherstuff" --prints--> "stuff% otherstuff" (an unclosed format specifier with infinite whitespace between translates to '%' and a single whitespace)
    // "stuff%      sotherstuff"   --prints--> "stuffSTRINGotherstuff" (a closed format specifier replaces everything from opening to closing format specifier -- with the variable meant to be there)


    // the algorithm:
    // PARSE THROUGH THE STRING STARTING FROM INDEX 0. all flags initially false.
    // get current character at string index

    // if format_flag == false and char not '%':
        // print the current character

    // else if format_flag == false and current char == '%':
        // format_flag = true

    // else if format_flag == true and current character == white_space:
        // white_space_flag = true

    // else if format_flag == true and current character not in alternate special characters:
        // format_flag = false
        // print '%'
        // if white_space_flag == true:
            // print a single whitespace
            // white_space_flag = false
        // print the current character
    
    // else if format_flag == true and current character in alternate special characters:
        // format_flag = false
        // white_space_flag = false
        // --PRINT ACTUAL VALUE. this means:--
        // if current character == '%':
            // print '%'
        // else if current character == 'c':
            // fetch argument from arg_ptr as a char type, and print it
        // else if current character == 's':
            // fetch argument from arg_ptr as a char* type, and print it
        // else if current character == 'd':
            // fetch argument from arg_ptr as an int, and print it using the printnum_as_chars() function


    // IMPLEMENTATION
    // PARSE THROUGH THE STRING STARTING FROM INDEX 0. all flags initially false.
    int i = 0;
    bool format_flag = false;
    bool whitespace_flag = false;

    while(string[i] != '\0'){

    if (format_flag == false && string[i] != '%')
        putchar(string[i]);

    else if (format_flag == false && string[i] == '%')
        format_flag = true;

    else if (format_flag == true && string[i] == ' ')
        whitespace_flag = true;

    else if ( (format_flag == true) && !(isin(alternate_special_chars, string[i])) ){
        format_flag = false;
        putchar('%');
        if (whitespace_flag == true){
            putchar(' ');
            whitespace_flag = false;
        }
        putchar(string[i]);
    }
    
    else if (format_flag == true && isin(alternate_special_chars, string[i])){
        format_flag = false;
        whitespace_flag = false;
        // --PRINT ACTUAL VALUE OF FORMAT SPECIFIER--
        if (string[i] == '%')
            putchar('%');
        else if (string[i] == 'c')
            // fetch argument from arg_ptr as a char type, and print it
            putchar(va_arg(arg_ptr, int));
        else if (string[i] == 's')
            // fetch argument from arg_ptr as a char* type, and print it
            puts(va_arg(arg_ptr, char*));
        else if (string[i] == 'd')
            // fetch argument from arg_ptr as an int, and print it using the printnum_as_chars() function
            printnum_as_chars(va_arg(arg_ptr, int));
        
        }

        i++;
    }

    va_end(arg_ptr);

    return 0; // TODO: return number of characters printed instead
}

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
    _printf("Option %c: In %d years, %d citizens will migrate from %s",option, years, migrants, country);

}