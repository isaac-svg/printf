#include "main.h"

/**
 * _printf - works same as  Printf function
 * @format: the  format string
 * Return: the  number of characters printed
 */
int _printf(const char *format, ...)
{
    int j, printed = 0, prnted_chars = 0;
    int flags, width, precision, size, buff_index = 0;
    va_list args;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (j = 0; format && format[j] != '\0'; j++)
    {
        if (format[j] != '%')
        {
            buffer[buff_index++] = format[j];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_index);
            prnted_chars++;
        }
	else
        {
            print_buffer(buffer, &buff_index);
            flags = get_flags(format, &j);
            width = get_width(format, &j, list);
            precision = get_precision(format, &j, list);
            size = get_size(format, &i);
            ++j;
            printed = handle_print(format, &j, list, buffer, flags, width, precision, size);
            if (printed == -1)
                return (-1);
            prnted_chars += printed;
        }
    }

    print_buffer(buffer, &buff_index);

    va_end(args);

    return (prnted_chars);
}

/**
 * print_buffer - Prints the contentents of the buffer
 * @buffer: Array containing characters
 * @buff_ind: Index at which to add the next character
 */
void print_buffer(char buffer[], int *buff_index)
{
    if (*buff_index > 0)
    {
        write(1, &buffer[0], *buff_index);
        *buff_index = 0;
    }
}
