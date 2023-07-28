#include "main.h"

/**
 * getSize - Extracts the size specifier for argument casting from format string
 * @format_string: Formatted string containing the arguments
 * @index_ptr: Pointer to track the position in the format string
 *
 * Return: Size specifier for argument casting
 */
int getSize(const char *format_string, int *index_ptr)
{
    int curr_index = *index_ptr + 1;
    int size_specifier = 0;

    if (format_string[curr_index] == 'l')
        size_specifier = SIZE_LONG;
    else if (format_string[curr_index] == 'h')
        size_specifier = SIZE_SHORT;

    if (size_specifier == 0)
        *index_ptr = curr_index - 1;
    else
        *index_ptr = curr_index;

    return size_specifier;
}
