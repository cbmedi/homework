/*
*   project: random array driver
*   compile: gcc -o homework rad.c -L./lib -lmedihwraf -lmedihwutils -lcrypto -g
*   library config:
*   under /etc/ld.so.conf.d create a homework.conf file
*       in the file put the path to where you installed the libmedihwraf.so and libmedihwutils.so file
*   run the command: sudo ldconfig to att your library to the LD_LIBRARY_PATH
*   run: ./homework 
*/
// headers
#include <stdio.h>

//my api headers
#include "libmedihwraf.h"
#include "libmedihwutils.h"

/*
This function casts the global statis struct RandomArray pointer object to
a struct RandomArray then uses the function pointer to thetto_string function
to make a call to the to_string function passing the address of the
struct RandomArray.

Input: 
    int argc:
    char **argv:
    
Output:
    int: signifying success or failure of the program
*/
int main(int argc, char **argv)
{
    unsigned char size = 100;

    // get an instance of IRandomarray
    struct IRandomArray * random_array_instance = new_irandom_array_factory(size);

    // call the print function
    puts("printing the random array");
    random_array_instance->print();

    // get instance ogf the internal random array
    char * random_char_array = random_array_instance->get_random_char_array();
    
    // sort the array
    // figure out the correct way to get array size
    puts("sorting the random array");
    msort(random_char_array, size, (sizeof(char)));

    //print the sorted array
    puts("printing the sorted array");
    random_array_instance->print_random_array(random_char_array);
 
    //testing singleton (** currently crashing**)
    puts("testing singleton");
    random_array_instance = new_irandom_array_factory(size);
    puts("printing the random array");
    random_array_instance->print();

    random_array_instance->clean_up();

    return 0;
}