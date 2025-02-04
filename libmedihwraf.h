#ifndef MEDIHWRAFSLIB_H 
#define MEDIHWRAFSLIB_H

// Include any necessary standard headers
// standard c
#include <stdio.h>
#include <string.h>

// openssl
#include <openssl/rand.h>

// required definitions
struct IRandomArray
{
    char * (* get_random_char_array)(void);
    void (* print)(void);
    void (* print_random_array)(char * random_char_array);
    void (* clean_up)(void);
};

// exposed methods
struct IRandomArray * new_irandom_array_factory(unsigned char size);
char * get_random_char_array(void);

#endif // MEDIHWRAFSLIB_H