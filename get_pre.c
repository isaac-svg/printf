#include "main.h"

/**
 * get_precision - Extracts the precision for printing from the format string
 * @format_string: Formatted string containing the arguments
 * @index_ptr: Pointer to track the position in the format string
 * @arg_list: List of arguments to be printed
 *
 * Return: Precision value
 */
int get_precision(const char *format_string, int *index_ptr, va_list arg_list)
{
    int current_index = *index_ptr + 1;
    int precision_value = -1;

    if (format_string[current_index] != '.')
        return precision_value;

    precision_value = 0;

    for (current_index += 1; format_string[current_index] != '\0'; current_index++)
    {
        if (is_digit(format_string[current_index]))
        {
            precision_value *= 10;
            precision_value += format_string[current_index] - '0';
        }
        else if (format_string[current_index] == '*')
        {
            current_index++;
            precision_value = va_arg(arg_list, int);
            break;
        }
        else
            break;
    }

    *index_ptr = current_index - 1;

    return precision_value;
}
