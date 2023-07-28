#include "main.h"

/************************* PRINT POINTER *************************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_pointer(va_list args, char buf[], int flags, int width, int precision, int size)
{
    char extra_char = 0, padding_char = ' ';
    int index = BUFF_SIZE - 2, length = 2, padding_start = 1; /* length=2, for '0x' */
    unsigned long int num_addresses;
    char hex_map[] = "0123456789abcdef";
    void *addresses = va_arg(args, void *);

    UNUSED(width);
    UNUSED(size);

    if (addresses == NULL)
        return (write(1, "(nil)", 5));

    buf[BUFF_SIZE - 1] = '\0';
    UNUSED(precision);

    num_addresses = (unsigned long int)addresses;

    while (num_addresses > 0)
    {
        buf[index--] = hex_map[num_addresses % 16];
        num_addresses /= 16;
        length++;
    }

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padding_char = '0';
    if (flags & F_PLUS)
        extra_char = '+', length++;
    else if (flags & F_SPACE)
        extra_char = ' ', length++;

    index++;

    return (write_pointer(buf, index, length, width, flags, padding_char, extra_char, padding_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non-printable chars
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list args, char buf[], int flags, int width, int precision, int size)
{
    int i = 0, offset = 0;
    char *str = va_arg(args, char *);

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        return (write(1, "(null)", 6));

    while (str[i] != '\0')
    {
        if (is_printable(str[i]))
            buf[i + offset] = str[i];
        else
            offset += append_hex_code(str[i], buf, i + offset);

        i++;
    }

    buf[i + offset] = '\0';

    return (write(1, buf, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_reverse(va_list args, char buf[], int flags, int width, int precision, int size)
{
    char *str;
    int i, char_count = 0;

    UNUSED(buf);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(size);

    str = va_arg(args, char *);

    if (str == NULL)
    {
        UNUSED(precision);
        str = ")Null(";
    }

    for (i = 0; str[i]; i++)
        ;

    for (i = i - 1; i >= 0; i--)
    {
        char z = str[i];
        write(1, &z, 1);
        char_count++;
    }

    return (char_count);
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_rot13string(va_list args, char buf[], int flags, int width, int precision, int size)
{
    char x;
    char *str;
    unsigned int i, j;
    int char_count = 0;
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    str = va_arg(args, char *);
    UNUSED(buf);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        str = "(AHYY)";

    for (i = 0; str[i]; i++)
    {
        for (j = 0; in[j]; j++)
        {
            if (in[j] == str[i])
            {
                x = out[j];
                write(1, &x, 1);
                char_count++;
                break;
            }
        }

        if (!in[j])
        {
            x = str[i];
            write(1, &x, 1);
            char_count++;
        }
    }

    return (char_count);
}
