#include "main.h"

/**
 * printHexa - Prints a hexadecimal number in lower or upper case
 *
 * @args: List of arguments containing the number to print
 * @map_to: Array of values to map the number to (either lower or upper case)
 * @buff: Buffer array to handle print
 * @flags: Calculates active flags (such as F_HASH, F_ZERO, etc.)
 * @char_flag: Flag character (such as 'x', 'X', etc.)
 * @width_spec: Width specifier for formatting
 * @precision_spec: Precision specifier for formatting
 * @size_spec: Size specifier (such as S_LONG, S_SHORT, etc.)
 *
 * Return: Number of characters printed
 */

int printHexa(va_list args, char map_to[], char buff[], int flags, char char_flag, int width_spec, int precision_spec, int size_spec)
{
    int i = BUFFER_SIZE - 2;
    unsigned long int num = va_arg(args, unsigned long int);
    unsigned long int init_num = num;

    UNUSED(width_spec);

    num = convertToSizeUnsgnd(num, size_spec);

    if (num == 0)
        buff[i--] = '0';

    buff[BUFFER_SIZE - 1] = '\0';

    while (num > 0)
    {
        buff[i--] = map_to[num % 16];
        num /= 16;
    }

    if (flags & FLAG_HASH && init_num != 0)
    {
        buff[i--] = char_flag;
        buff[i--] = '0';
    }

    i++;

    return (writeUnsgnd(0, i, buff, flags, width_spec, precision_spec, size_spec));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * printOctal - Prints an unsigned number in octal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width_spec: Width specifier
 * @precision_spec: Precision specification
 * @size_spec: Size specifier
 *
 * Return: Number of characters printed
 */
int printOctal(va_list args, char buffer[], int flags, int width_spec, int precision_spec, int size_spec)
{
    int i = BUFFER_SIZE - 2;
    unsigned long int num = va_arg(args, unsigned long int);
    unsigned long int init_num = num;

    UNUSED(width_spec);

    num = convertToSizeUnsgnd(num, size_spec);

    if (num == 0)
        buffer[i--] = '0';

    buffer[BUFFER_SIZE - 1] = '\0';

    while (num > 0)
    {
        buffer[i--] = (num % 8) + '0';
        num /= 8;
    }

    if (flags & FLAG_HASH && init_num != 0)
        buffer[i--] = '0';

    i++;

    return (writeUnsgnd(0, i, buffer, flags, width_spec, precision_spec, size_spec));
}

/************* PRINT UNSIGNED NUMBER *************************/
/**
 * printUnsigned - Prints an unsigned number
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width_spec: Width specifier
 * @precision_spec: Precision specification
 * @size_spec: Size specifier
 *
 * Return: Number of characters printed
 */
int printUnsigned(va_list args, char buffer[], int flags, int width_spec, int precision_spec, int size_spec)
{
    int i = BUFFER_SIZE - 2;
    unsigned long int num = va_arg(args, unsigned long int);

    num = convertToSizeUnsgnd(num, size_spec);

    if (num == 0)
        buffer[i--] = '0';

    buffer[BUFFER_SIZE - 1] = '\0';

    while (num > 0)
    {
        buffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (writeUnsgnd(0, i, buffer, flags, width_spec, precision_spec, size_spec));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * printHexadecimal - Prints an unsigned number in hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width_spec: Width specifier
 * @precision_spec: Precision specification
 * @size_spec: Size specifier
 *
 * Return: Number of characters printed
 */
int printHexadecimal(va_list args, char buffer[], int flags, int width_spec, int precision_spec, int size_spec)
{
    return (printHexa(args, "0123456789abcdef", buffer, flags, 'x', width_spec, precision_spec, size_spec));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * printHexaUpper - Prints an unsigned number in upper hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width_spec: Width specifier
 * @precision_spec: Precision specification
 * @size_spec: Size specifier
 *
 * Return: Number of characters printed
 */
int printHexUpper(va_list args, char buffer[], int flags, int width_spec, int precision_spec, int size_spec)
{
    return (printHexa(args, "0123456789ABCDEF", buffer, flags, 'X', width_spec, precision_spec, size_spec));
}
