#include "main.h"

/**
 * get_size - Extracts the size specifier for argument casting from format string
 * @format_string: Formatted string containing the arguments
 * @index_ptr: Pointer to track the position in the format string
 *
 * Return: Size specifier for argument casting
 */
int get_size(const char *format_string, int *index_ptr)
{
    int curr_index = *index_ptr + 1;
    int size_specifier = 0;

    if (format_string[curr_index] == 'l')
        size_specifier = S_LONG;
    else if (format_string[curr_index] == 'h')
        size_specifier = S_SHORT;

    if (size_specifier == 0)
        *index_ptr = curr_index - 1;
    else
        *index_ptr = curr_index;

    return size_specifier;
}
