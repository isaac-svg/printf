#include "main.h"

/**
 * handlePrint - Prints an argument based on its type
 * @format: Formatted string containing the arguments
 * @index: Index to track the position in the format string
 * @arg_list: List of arguments to be printed
 * @buffer: Buffer array to handle print
 * @flags: Calculated active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of characters printed or -1 if an unknown format specifier is found
 */
int handlePrint(const char *format, int *index, va_list arg_list,
                 char buffer[], int flags, int width, int precision, int size)
{
    int i, unknown_len = 0, printed_chars = -1;

    typedef struct {
        char fmt;
        int (*fn)(va_list, char[], int, int, int, int);
    } FormatType;

    FormatType fmt_types[] = {
        {'c', printChar}, {'s', printString}, {'%', printPercent},
        {'i', printInt}, {'d', printInt}, {'b', printBinary},
        {'u', printUnsigned}, {'o', printOctal}, {'x', printHexadecimal},
        {'X', printHexUpper}, {'p', printPointer}, {'S', printNonPrintable},
        {'r', printReverse}, {'R', printRot13string}, {'\0', NULL}
    };

    for (i = 0; fmt_types[i].fmt != '\0'; i++)
    {
        if (format[*index] == fmt_types[i].fmt)
            return fmt_types[i].fn(arg_list, buffer, flags, width, precision, size);
    }

    if (fmt_types[i].fmt == '\0')
    {
        if (format[*index] == '\0')
            return -1;

        unknown_len += write(1, "%%", 1);

        if (format[*index - 1] == ' ')
            unknown_len += write(1, " ", 1);
        else if (width)
        {
            --(*index);
            while (format[*index] != ' ' && format[*index] != '%')
                --(*index);
            if (format[*index] == ' ')
                --(*index);
            return 1;
        }

        unknown_len += write(1, &format[*index], 1);
        return unknown_len;
    }

    return printed_chars;
}
