/*
*   compile: gcc -shared -o lib/libmedihwutils.so utils.c
*/

#include "libmedihwutils.h"

/*
This function compares two values using math.

Input: 
    const void * a:
    const void * b:
    
Output:
    int: signifies if the 2 numbers are equal
        -n, 0, n
*/
static int comp(const void * a, const void * b)
{
    return * (char *) a - * (char *) b;
}

/*
This function wraps the stdlib sort function, a char pointer, length of
the array, and value size, plus a pointer to the comparator function is
opassed to the sort.

Input: 
    char * random_char_array: a none null pointer to the array to be sorted
    int length: length of the array
    int value_size: size of the array values
    
Output: there is no return value.
*/
void msort(char * random_char_array, int length, int value_size)
{
    qsort(random_char_array, length, value_size, comp);
}