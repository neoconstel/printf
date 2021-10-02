#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

// we're aiming for something like this below:
// _printf("In %d years, %d citizens will migrate from %s", years, migrants, country);
// outout: In 3 years, 781 citizens will migrate from Florida
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

char alternate_special_chars[] = {'%','c','d','e','f','g','i','o','s','u','x','\0'};

int _printf(const char *string, ...);

int _printf(const char *string, ...)
{
    // first count how many VALID format specifiers (how many valid opening '%' are closed with an alternate special charater )
    // so we can use it to initialize the argument pointer later on (via va_start)
    // these are valid:
    //      "The child of %d years went to school"  
    //      "The girl named %   s was sent from the class" (white space does not terminate the open '%)

    // But this is not valid:
    //      "The girl named % z  s was sent from the class" (any character not in our list of alternate special characters terminates the open '%)

    int format_specs = 0;
    bool format_flag = false;   //true if % is 'open', and closed by any matching character from the alternate special characters list. E.g %c, %d or %%
    int i = 0;

    while (string[i] != '\0')
    {
        if (string[i] !=' ' && !(isin(alternate_special_chars, string[i]) ) ){
            format_flag = false;
        }            

        else if ( string[i] == '%' && format_flag == false )
        {
            format_flag = true;
        }
        
        else if ( isin(alternate_special_chars, string[i]) && format_flag == true )
        {
            format_specs++;
            format_flag = false;
        }

        else
            ;
        
        i++;    
    }
    

    /*Tap into the variable arguments and alternate between the format
    specifiers in the first(string) argument and the corresponding variables
    in the variable arguments. Return the corresponding type from va_arg 
    according to the corresponding formaat specifier. Append the interpreted forms
    of the variable in each case into a single string.*/

    return format_specs; // must delete this return statement. It's just to test-check number of formatters found for now
}

int main(void)
{
    // testing number of string formatters found
    char *string1 = "%"; //single opening '%', no closing character = 0 valid specifiers
    char *string2 = "%%%%%%"; //3 sequences of opening/closing '%' = 3 valid specifiers
    char *string3 = "stuff %c %d stuff %z %j %99"; // 2 valid specifiers (%c and %d). Because z, j and 9 are not included in our list of alternate special characters.
    char *string4 = "% z %d %  s stuff"; // Total = 2 valid specifiers => First opening '%' terminated by z(which is not in alternate special characters). %d is valid (1 count). %  s is valid, since whitespace does not terminate the open '%'. 

    printf("Formatters in string 1: %d\n", _printf(string1));
    printf("Formatters in string 2: %d\n", _printf(string2));
    printf("Formatters in string 3: %d\n", _printf(string3));
    printf("Formatters in string 4: %d\n", _printf(string4));
}