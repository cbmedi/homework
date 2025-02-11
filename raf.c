/*
*   project: random array factory
*   compile: gcc -shared -fPIC -o lib/libmedihwraf.so raf.c
*   library config:
*   under /etc/ld.so.conf.d create a homework.conf file
*       in the file put the path to where you installed the libmedihwraf.so file
*   run the command: sudo ldconfig to att your library to the LD_LIBRARY_PATH
*/

// my header
#include "libmedihwraf.h"

// my defines
typedef char bool;

/*
    class that uses interface struct IRandomArray, plus a few of its own
    function pointers and the arrays needed.
*/
typedef struct RandomArray{
    struct IRandomArray random_array_interface;
    bool (* value_already_inserted)(void * obj, char value_to_check);
    bool (* values_are_consecutive)(void * obj, char value, char value_being_compared_to);
    void (* insert_value)(void * obj, char value);
    void (* increment_duplicate_found)(void * obj, char value);
    void (* to_string)(void * obj);
    void (* print_array_to_format)(char * array_to_print, unsigned char size);
    // reference to myself
    //void * this;
    // array to track if we already inserted this number
    char size;
    char * random_char_array;
    bool * track_array;
    int * duplicate_select_array;
    short random_char_array_index;
} RandomArray_s;

/*
    Variable to hold our struct RandomArray pointer so we always return
    the same one after the initial memory allocation.
*/
static RandomArray_s * raf_random_array_singlton = NULL;

//future define

/*
This function returns a pointer to our random_char_array to the
caller.

Input: 
    No input.
    
Output:
    random_char_array: pointer to our 
*/
char * get_random_char_array(void)
{
    return (*raf_random_array_singlton).random_char_array;
}

/*
This function casts the global statis struct RandomArray pointer object to
a struct RandomArray then uses the function pointer to thetto_string function
to make a call to the to_string function passing the address of the
struct RandomArray.

Input: 
    No input.
    
Output: there is no return value.
*/
void print(void)
{
    // get instance of ourselves
    RandomArray_s random_array_instance = *raf_random_array_singlton;

    random_array_instance.to_string(&random_array_instance);
}

/*
This function converts obj to a struct RandomArray pointer then
passes the char pointer to the print_array_to_format function using
the assigned function pointer.

Input: 
    vchar * random_char_array: none null pointer to a char array
    
Output: there is no return value.
*/
void print_random_array(char * random_char_array)
{
    // get instance of ourselves
    RandomArray_s * random_array_instance = (RandomArray_s *) raf_random_array_singlton;

    random_array_instance->print_array_to_format(random_char_array, random_array_instance->size);
}

/*
This function frees the allocated memory for our member arrays and
for our object.

Input: 
    No input.
    
Output: there is no return value.
*/
void clean_up(void)
{
    if(NULL != raf_random_array_singlton)
    {
        if(NULL != raf_random_array_singlton->duplicate_select_array)
        {
            free(raf_random_array_singlton->duplicate_select_array);
        }

        if(NULL != raf_random_array_singlton->track_array)
        {
            free(raf_random_array_singlton->track_array);
        }

        if(NULL != raf_random_array_singlton->random_char_array)
        {
            free(raf_random_array_singlton->random_char_array);
        }

        free(raf_random_array_singlton);
    }
}

/*
This function checks if we already entered this value in our array.

Input: 
    void * obj: none null pointer to a struct RandomArray *
    char value_to_check: the value to be tested
    
Output: a true or false is returned.
*/
//   maybe add size
bool value_already_inserted(void * obj, char value_to_check)
{
    // get instance of ourselves
    RandomArray_s * this = (RandomArray_s *) obj;
    return this->track_array[value_to_check];
}

/*
This function converts obj to a struct RandomArray pointer
and takes 2 values to compare to make sure they are not concecutive.
Acomparison is done only after the track_array hasa value set
at index 0. If by chance the last element of the array is
concecutive to the previous element value then we are stuck
in a never ending loop.

Input: 
    void * obj: none null pointer to a struct RandomArray *
    char value: the value to be tested
    char value_being_compared_to: the value tested against
    
Output: a true or false is returned.
*/
// this should solve 99% of the possibilities except when the last char to pick is consecutive
bool values_are_consecutive(void * obj, char value, char value_being_compared_to)
{
    // get instance of ourselves
    RandomArray_s * this = (RandomArray_s *) obj;

    return (
        this->random_char_array_index
        &&
        (
            (1 == value - value_being_compared_to) // 70 - 69 = 1
            || 
            (-1 == value - value_being_compared_to) // 70 - 71 = -1
        )
    );
}

/*
This function converts obj to a struct RandomArray pointer
then inserts a value in the random_char_array member and increments
the random_char_array_index member by 1, the value in the track_array member at
array index of value is also incremented.

Input: 
    void * obj: none null pointer to a struct RandomArray *
    char value: the value that shold be inserted
    
Output: there is no return value.
*/
void insert_value(void * obj, char value)
{
    // get instance of ourselves
    RandomArray_s * this = (RandomArray_s *) obj;

    this->random_char_array[this->random_char_array_index++] = value;
    this->track_array[value]++;
}

/*
This function converts obj to a struct RandomArray pointer
then increments the value at the value index of the duplicate_select_array
member by 1.

Input: 
    void * obj: none null pointer to a struct RandomArray *
    
Output: there is no return value.
*/
void increment_duplicate_found(void * obj, char value)
{
    // get instance of ourselves
    RandomArray_s * this = (RandomArray_s *) obj;

    this->duplicate_select_array[value]++;
}

/*
This function prints out rows of 10 characters out of a character array upto
the limit speified by size.

Input: 
    char * array_to_print: pointer to an array of characters
    unsigned char size: size of the array
    
Output: there is no return value.
*/
void print_array_to_format(char * array_to_print, unsigned char size)
{
    // we should figure out the array size
    for(short current_index = 0; current_index < size; current_index++)
    {
        // print the integer
        printf(" %02d", array_to_print[current_index]);

        // every 10th integer write a new line
        if(9 == (current_index % 10))
        {
            puts("\n");
        }
    }

    puts("\n");
}

/*
This function converts obj to a struct RandomArray pointer then
gets a pointer to the random_char_array member and passes that
pointer to the print_array_tp_format function.

Input: 
    void * obj: none null pointer to a struct RandomArray *
    
Output: there is no return value.
*/
void to_string(void * obj)
{
    // get instance of ourselves
    RandomArray_s * this = (RandomArray_s *) obj;
    // get array to print
    char * random_char_array = {this->random_char_array};

    this->print_array_to_format(random_char_array, this->size);
}

/*
This function allocates a struct RandomArray.

Input: 
    unsigned char size: size of the random_array to be contained by the
    struct RandomArray object, if that allocation is successful then an
    allocation of size of array * size sent my caller is done for each of
    following memebers:
        random_char_array
        track_array
        duplicate_select_array
    The arrays values are then zeroed oout for each array element.
    Function pointers are assigned to the random_array_interface members for
    the following functions:
        print 
        print_random_array
        get_random_char_array
        clean_up
    Function pointers are also assigned for the following members for the
    following functions:
        increment_duplicate_found;
        insert_value;
        print_array_to_format;
        to_string;
        value_already_inserted;
    Random numbers are requested from the openssl RAND_bytes and placed in
    the track_array if they have not already been added, duplicates are logged
    in the duplicate_select_array.
    The global variable raf_random_array_singlton is assigned the resulting
    allocation and the raf_random_array_singlton is returned to the function
    caller.
    
Output:
    NULL or a pointer to a struct RandomArray * object.
*/
RandomArray_s * new_random_array_fatory(unsigned char size)
{
    if(NULL == raf_random_array_singlton)
    {
        //define and allocat the RandomArray structure
        RandomArray_s * random_array = malloc(sizeof(RandomArray_s));
        
        //check that memory allocation did not fail
        if(NULL == random_array)
        {
            return NULL;
        }
        
        //allocate the random char array
        random_array->random_char_array = calloc(sizeof(random_array->random_char_array) * size, sizeof(random_array->random_char_array));

        if(NULL == random_array->random_char_array)
        {
            free(random_array);
            return NULL;
        }
        //allocate the random char array
        random_array->track_array = calloc(sizeof(random_array->track_array) * size, sizeof(random_array->track_array));

        if(NULL == random_array->track_array)
        {
            free(random_array);
            return NULL;
        }

        //allocate the random char array
        random_array->duplicate_select_array = calloc(sizeof(random_array->duplicate_select_array) * size, sizeof(random_array->duplicate_select_array));

        if(NULL == random_array->duplicate_select_array)
        {
            free(random_array);
            return NULL;
        }

        random_array->size = size;
        random_array->random_char_array_index;

        // 0 out all the arraysthis
        //memset(random_array->random_char_array, 0, random_array->size * sizeof(random_array->random_char_array[0]));
        //memset(random_array->track_array, 0, random_array->size * sizeof(random_array->track_array[0]));
        //memset(random_array->duplicate_select_array, 0, random_array->size * sizeof(random_array->duplicate_select_array[0]));

        random_array->random_char_array_index = 0;

        // set IRandomArray functions
        random_array->random_array_interface.print = print;
        random_array->random_array_interface.print_random_array = print_random_array;
        random_array->random_array_interface.get_random_char_array = get_random_char_array;
        random_array->random_array_interface.clean_up = clean_up;

        // set RandomArray functions
        random_array->increment_duplicate_found = increment_duplicate_found;
        random_array->insert_value = insert_value;
        random_array->print_array_to_format = print_array_to_format;
        random_array->to_string = to_string;
        random_array->value_already_inserted = value_already_inserted;
        random_array->values_are_consecutive = values_are_consecutive;

        unsigned char buf [1] = {-1};

        while(random_array->random_char_array_index < random_array->size)
        {
            if(1 == RAND_bytes(buf, 1))
            {
                char char_to_be_inserted = buf[0] % random_array->size;

                if(
                    (!random_array->value_already_inserted(random_array, char_to_be_inserted))
                    &&
                    (!random_array->values_are_consecutive(
                        random_array,
                        char_to_be_inserted,
                        random_array->random_char_array[random_array->random_char_array_index-1])
                    )
                )
                {
                    
                    // insert the char in to the random_char_array
                    random_array->insert_value(random_array, char_to_be_inserted);
                }
                else
                {
                    //increment duplicate value
                    random_array->increment_duplicate_found(random_array, char_to_be_inserted);
                }
            }
        }

        raf_random_array_singlton = random_array;
    }

    return raf_random_array_singlton;
}

/*
This function makes a call to the new_random_array_factory to get a
struct RandomArray pointer which is then cast to a 
struct IRandomArray pointer and returned to the function caller.

Input: 
    unsigned char size: size of the random_arry to be contained by the
    struct IRandomArray object.
    
Output:
    NULL or a pointer to a struct IRandomArray object.
*/
IRandomArray_s * new_irandom_array_factory(unsigned char size)
{
    RandomArray_s * random_array = new_random_array_fatory(size);

    return (IRandomArray_s *)random_array;
}