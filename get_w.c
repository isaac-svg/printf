#include "main.h"

/**
 * get_width - Extracts the width specifier for printing from the format string
 * @format_str: Formatted string containing the arguments
 * @index_ptr: Pointer to track the position in the format string
 * @arg_list: List of arguments to be printed
 *
 * Return: Width specifier for printing
 */
int get_width(const char *format_str, int *index_ptr, va_list arg_list)
{
    int curr_index;
    int width_spec = 0;

    for (curr_index = *index_ptr + 1; format_str[curr_index] != '\0'; curr_index++)
    {
        if (is_digit(format_str[curr_index]))
        {
            width_spec *= 10;
            width_spec += format_str[curr_index] - '0';
        }
        else if (format_str[curr_index] == '*')
        {
            curr_index++;
            width_spec = va_arg(arg_list, int);
            break;
        }
        else
            break;
    }

    *index_ptr = curr_index - 1;

    return width_spec;
}
