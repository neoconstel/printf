#include <unistd.h>
#include <stdarg.h>



/*
* we're aiming for something like this below for _printf:
* _printf("Option %c: In %d years, %d citizens will migrate from %s",
                                            option, years, migrants, country);
* option:     'B'      (char)
* years:       3       (int)
* migrants:    781     (int)
* country:     "Florida" (string)
* output: Option B: In 3 years, 781 citizens will migrate from Florida
* ------------------------------------------------------
*/

// function to return 1 if the character c is in the string else 0
int isin(char *string, const char c)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (c == string[i++])
            return 1;
    }
    return 0;      
}


// function to return number of valid formatters in a string
int count_valid_formatters(const char *string, ...)
{    
    // these are valid:
    //      "The child of %d years went to school"  
    //      "The girl named %   s was sent from the class" (white space does not terminate the open '%)

    // But this is not valid:
    //      "The girl named % z  s was sent from the class" (any character not in our list of alternate special characters terminates the open '%)

    char alternate_special_chars[] = {'%','c','d','e','f','g','i','o','s','u','x'};
    int format_specifiers = 0;
    int format_flag = 0;   //1 if % is 'open', and closed by any matching character from the alternate special characters list. E.g %c, %d or %%
    int i = 0;

    while (string[i] != '\0') // while we aren't yet at the end of the string
    {
        // if the current character is not a space and is not in our list of alternate special characters
        if (string[i] !=' ' && !(isin(alternate_special_chars, string[i]) ) ){
            format_flag = 0;
        }            

        // else if current character is '%' and the format flag is 0
        else if ( string[i] == '%' && format_flag == 0 )
        {
            format_flag = 1;
        }
        
        // else if current character is in our list of alternate special characters and the format flag is 1
        else if ( isin(alternate_special_chars, string[i]) && format_flag == 1 )
        {
            format_specifiers++;
            format_flag = 0;
        }

        else
            ; // do nothing
        
        i++;  // increment i for checking the next index (position) in the string
    }    

    return format_specifiers;
}


int printnum_as_chars(long n){
    
    int is_negative;
    char character[1];

    // something to store the number length
    int characters_printed = 0;

    //ensure we are working with the absolute value of the number
    is_negative = n < 0? 1:0;
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
        character[0] = '-';
        write(1, character, 1);
        characters_printed++;
    }

    // get/print digits, starting from highest value(4)
    int digit;
    int i = 0; //for storing the character form of the digit at index position of the buffer    
    do{
        digit = (n % divisor_10 - n % divisor) / divisor;            
        // print character equivalent of digit
        character[0] = '0' + digit;
        write(1, character, 1);
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
    char alternate_special_chars[] = {'%','c','d','e','f','g','i','o','s','u','x'};
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
    // PARSE THROUGH THE STRING STARTING FROM INDEX 0. all flags initially 0.
    // get current character at string index

    // if format_flag == 0 and char not '%':
        // print the current character

    // else if format_flag == 0 and current char == '%':
        // format_flag = 1

    // else if format_flag == 1 and current character == white_space:
        // white_space_flag = 1

    // else if format_flag == 1 and current character not in alternate special characters:
        // format_flag = 0
        // print '%'
        // if white_space_flag == 1:
            // print a single whitespace
            // white_space_flag = 0
        // print the current character
    
    // else if format_flag == 1 and current character in alternate special characters:
        // format_flag = 0
        // white_space_flag = 0
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
    // PARSE THROUGH THE STRING STARTING FROM INDEX 0. all flags initially 0.
    int i = 0;
    int format_flag = 0;
    int whitespace_flag = 0;
    char character[1];
    int total_characters = 0;

    while(1){

    if (format_flag == 0 && string[i] != '%' && string[i] != '\0'){
        character[0] = string[i];
        write(1, character, 1);
        total_characters++;
        }

    else if (format_flag == 0 && string[i] == '%')
        format_flag = 1;

    else if (format_flag == 1 && string[i] == ' ')
        whitespace_flag = 1;

    else if ( (format_flag == 1) && !(isin(alternate_special_chars, string[i])) ){
        format_flag = 0;
        character[0] = '%';
        write(1, character, 1);
        total_characters++;
        if (whitespace_flag == 1){
            character[0] = ' ';
            write(1, character, 1);
            total_characters++;
            whitespace_flag = 0;
        }

        // only write the non-special-character if it is not the null terminator
        if (string[i] != '\0') {
        character[0] = string[i];
        write(1, character, 1);
        total_characters++;
        }
    }
    
    else if (format_flag == 1 && isin(alternate_special_chars, string[i])){
        format_flag = 0;
        whitespace_flag = 0;
        // --PRINT ACTUAL VALUE OF FORMAT SPECIFIER--
        if (string[i] == '%'){
            character[0] = '%';
            write(1, character, 1);
            total_characters++;
        }
        else if (string[i] == 'c'){
            // fetch argument from arg_ptr as a char type, and print it
            character[0] = va_arg(arg_ptr, int);
            write(1, character, 1);
            total_characters++;
        }
        else if (string[i] == 's'){
            // fetch argument from arg_ptr as a char* type, and print it
            char *string_arg = va_arg(arg_ptr, char*);
            int string_length = 0;
            for (; string_arg[string_length] != '\0'; string_length++ )
                ;
            write(1, string_arg, string_length );
            total_characters += string_length;
        }
        else if (string[i] == 'd' || string[i] == 'i')
            // fetch argument from arg_ptr as an int, and print it using the printnum_as_chars() function
            total_characters += printnum_as_chars(va_arg(arg_ptr, int));
        
        }

        if (string[i] == '\0')
            break;

        i++;
    }

    va_end(arg_ptr);

    return total_characters;
}

