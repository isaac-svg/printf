#include "main.h"

/**
 * printChar - Prints a single character.
 * @args: List of arguments containing the character to print.
 * @buf: Buffer array to handle the print operation.
 * @fl: Flags that calculate the active formatting options.
 * @w: Width specifier for the formatted output.
 * @prec: Precision specification for the formatted output.
 * @sz: Size specifier for the formatted output.
 *
 * Return: The number of characters printed.
 */
int printChar(va_list args, char buf[], int fl, int w, int prec, int sz)
{
    char ch = va_arg(args, int);

    return (handleWriteChar(ch, buf, fl, w, prec, sz));
}

/**
 * printString - Prints a string.
 * @args: List of arguments containing the string to print.
 * @buf: Buffer array to handle the print operation.
 * @fl: Flags that calculate the active formatting options.
 * @w: Width specifier for the formatted output.
 * @prec: Precision specification for the formatted output.
 * @sz: Size specifier for the formatted output.
 *
 * Return: The number of characters printed.
 */
int printString(va_list args, char buf[], int fl, int w, int prec, int sz)
{
    int len = 0, i;
    char *s = va_arg(args, char *);

    UNUSED(buf);
    UNUSED(fl);
    UNUSED(w);
    UNUSED(prec);
    UNUSED(sz);

    if (s == NULL)
    {
        s = "(null)";
        if (prec >= 6)
            s = "      ";
    }

    while (s[len] != '\0')
        len++;

    if (prec >= 0 && prec < len)
        len = prec;

    if (w > len)
    {
        if (fl & FLAG_MINUS)
        {
            write(1, &s[0], len);
            for (i = w - len; i > 0; i--)
                write(1, " ", 1);
            return (w);
        }
        else
        {
            for (i = w - len; i > 0; i--)
                write(1, " ", 1);
            write(1, &s[0], len);
            return (w);
        }
    }

    return (write(1, s, len));
}

/**
 * printPercent - Prints a percent sign.
 * @args: List of arguments (unused in this function).
 * @buf: Buffer array to handle the print operation.
 * @fl: Flags that calculate the active formatting options (unused in this function).
 * @w: Width specifier for the formatted output (unused in this function).
 * @prec: Precision specification for the formatted output (unused in this function).
 * @sz: Size specifier for the formatted output (unused in this function).
 *
 * Return: The number of characters printed (always 1 for the percent sign).
 */
int printPercent(va_list args, char buf[], int fl, int w, int prec, int sz)
{
    UNUSED(args);
    UNUSED(buf);
    UNUSED(fl);
    UNUSED(w);
    UNUSED(prec);
    UNUSED(sz);

    return (write(1, "%%", 1));
}

/**
 * printInt - Prints an integer.
 * @args: List of arguments containing the integer to print.
 * @buf: Buffer array to handle the print operation.
 * @fl: Flags that calculate the active formatting options.
 * @w: Width specifier for the formatted output.
 * @prec: Precision specification for the formatted output.
 * @sz: Size specifier for the formatted output.
 *
 * Return: The number of characters printed.
 */
int printInt(va_list args, char buf[], int fl, int w, int prec, int sz)
{
    int i = BUFFER_SIZE - 2;
    int is_neg = 0;
    long int num = va_arg(args, long int);
    unsigned long int n;

    num = convertToSizeNumber(num, sz);

    if (num == 0)
        buf[i--] = '0';

    buf[BUFFER_SIZE - 1] = '\0';
    n = (unsigned long int)num;

    if (num < 0)
    {
        n = (unsigned long int)((-1) * num);
        is_neg = 1;
    }

    while (n > 0)
    {
        buf[i--] = (n % 10) + '0';
        n /= 10;
    }

    i++;

    return (writeNumber(is_neg, i, buf, fl, w, prec, sz));
}

/**
 * printBinary - Prints an unsigned integer in binary format.
 * @args: List of arguments containing the integer to print in binary format.
 * @buf: Buffer array to handle the print operation.
 * @fl: Flags that calculate the active formatting options (unused in this function).
 * @w: Width specifier for the formatted output (unused in this function).
 * @prec: Precision specification for the formatted output (unused in this function).
 * @sz: Size specifier for the formatted output (unused in this function).
 *
 * Return: The number of characters printed.
 */
int printBinary(va_list args, char buf[], int fl, int w, int prec, int sz)
{
    unsigned int num, mask, i, sum;
    unsigned int bits[32];
    int cnt;

    UNUSED(buf);
    UNUSED(fl);
    UNUSED(w);
    UNUSED(prec);
    UNUSED(sz);

    num = va_arg(args, unsigned int);
    mask = 2147483648; /* (2 ^ 31) */
    bits[0] = num / mask;
    for (i = 1; i < 32; i++)
    {
        mask /= 2;
        bits[i] = (num / mask) % 2;
    }
    for (i = 0, sum = 0, cnt = 0; i < 32; i++)
    {
        sum += bits[i];
        if (sum || i == 31)
        {
            char z = '0' + bits[i];

            write(1, &z, 1);
            cnt++;
        }
    }
    return (cnt);
}
