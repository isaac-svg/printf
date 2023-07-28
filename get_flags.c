#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @index: Index to track the position in the format string
 * Return: Flags representing active formatting options
 */
int get_flags(const char *format, int *index)
{
    /* - + 0 # ' ' */
    /* 1 2 4 8  16 */
    int j, curr_index;
    int flags = 0;
    const char FLAGS_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (curr_index = *index + 1; format[curr_index] != '\0'; curr_index++)
    {
        for (j = 0; FLAGS_CHARACTERS[j] != '\0'; j++)
        {
            if (format[curr_index] == FLAGS_CHARACTERS[j])
            {
                flags |= FLAGS_ARRAY[j];
                break;
            }
        }

        if (FLAGS_CHARACTERS[j] == 0)
            break;
    }

    *index = curr_index - 1;

    return (flags);
}
