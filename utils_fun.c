#include "main.h"

/**
 * isPrintableChar - Evaluates if a char is printable
 * @ch: Char to be evaluated
 *
 * Return: 1 if ch is printable else 0
 */
int isPrintableChar(char ch)
{
    if (ch >= 32 && ch < 127)
        return 1;
    return 0;
}

/**
 * appendHexCode - Append ASCII in hexadecimal code
 * @buffer: Array of characters.
 * @index: Index at which to start appending.
 * @ascii_code: ASCII CODE.
 * Return: Always 3
 */
int appendHexCode(char ascii_code, char buffer[], int index)
{
    char hex_map[] = "0123456789ABCDEF";
    /* The hex format code is always 2 digits long */
    if (ascii_code < 0)
        ascii_code *= -1;

    buffer[index++] = '\\';
    buffer[index++] = 'x';

    buffer[index++] = hex_map[ascii_code / 16];
    buffer[index] = hex_map[ascii_code % 16];

    return 3;
}

/**
 * isDigitChar - Verifies if a char is a digit
 * @ch: Char to be evaluated
 *
 * Return: 1 if ch is a digit, 0 otherwise
 */
int isDigitChar(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

/**
 * convertToSizeNumber - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convertToSizeNumber(long int num, int size)
{
    if (size == SIZE_LONG)
        return num;
    else if (size == SIZE_SHORT)
        return (short)num;

    return (int)num;
}

/**
 * convertToSizeUnsgnd - Casts an unsigned number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
unsigned int convertToSizeUnsgnd(unsigned long int num, int size)
{
    if (size == SIZE_LONG)
        return num;
    else if (size == SIZE_SHORT)
        return (unsigned short)num;

    return (unsigned int)num;
}