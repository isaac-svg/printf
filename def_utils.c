#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handleWriteChar - Prints a single character
 * @c: The character to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int handleWriteChar(char c, char buffer[], int flags, int width, int precision, int size)
{
	int i = 0;
    	char padd = ' ';

   	UNUSED(precision);
    	UNUSED(size);

    	if (flags & FLAG_ZERO)
        	padd = '0';

    	buffer[i++] = c;
    	buffer[i] = '\0';

    	if (width > 1)
    	{
        	buffer[BUFFER_SIZE - 1] = '\0';
        	for (i = 0; i < width - 1; i++)
            		buffer[BUFFER_SIZE - i - 2] = padd;

        	if (flags & FLAG_MINUS)
            		return (write(1, &buffer[0], 1) + write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
        	else
            		return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
    	}

    	return (write(1, &buffer[0], 1));
}

/**
 * writeNumber - Prints a signed number
 * @is_negative: Indicates if the number is negative.
 * @ind: Index at which the number starts on the buffer.
 * @buffer: Buffer array to handle print.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int writeNumber(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - ind - 1;
    	char padd = ' ', extra_ch = 0;

    	UNUSED(size);

    	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
        	padd = '0';
    	if (is_negative)
        	extra_ch = '-';
    	else if (flags & FLAG_PLUS)
        	extra_ch = '+';
    	else if (flags & FLAG_SPACE)
        	extra_ch = ' ';

    	return (writeNum(ind, buffer, flags, width, precision,
                      length, padd, extra_ch));
}

/**
 * writeNum - Write a number using a buffer
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle print.
 * @flags: Active flags.
 * @width: Width specifier.
 * @prec: Precision specifier.
 * @length: Number length.
 * @padd: Padding character.
 * @extra_c: Extra character.
 *
 * Return: Number of characters printed.
 */
int writeNum(int ind, char buffer[], int flags, int width, int prec, int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0' && width == 0)
        	return (0); /* printf(".0d", 0)  no char is printed */
    	if (prec == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
        	buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
    	if (prec > 0 && prec < length)
        	padd = ' ';

    	while (prec > length)
        	buffer[--ind] = '0', length++;

    	if (extra_c != 0)
        	length++;

    	if (width > length)
    	{
        	for (i = 1; i < width - length + 1; i++)
            	buffer[i] = padd;
        	buffer[i] = '\0';
        	if (flags & FLAG_MINUS && padd == ' ') /* Assign extra char to the left of buffer */
        	{
            		if (extra_c)
                	buffer[--ind] = extra_c;
            		return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
        	}
        else if (!(flags & FLAG_MINUS) && padd == ' ') /* Assign extra char to the left of buffer */
        {
	       	if (extra_c)
                buffer[--ind] = extra_c;
            	return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
        }
        else if (!(flags & FLAG_MINUS) && padd == '0') /* Assign extra char to the left of padding */
        {
		if (extra_c)
                buffer[--padd_start] = extra_c;
            	return (write(1, &buffer[padd_start], i - padd_start) +
                    write(1, &buffer[ind], length - (1 - padd_start)));
        }
    }
	if (extra_c)
        	buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * writeUnsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the number is negative.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle print.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters written.
 */
int writeUnsgnd(int is_negative, int ind,
                 char buffer[], int flags, int width, int precision, int size)
{
    /* The number is stored at the buffer's right and starts at position i */
    int length = BUFFER_SIZE - ind - 1, i = 0;
    char padd = ' ';

    UNUSED(is_negative);
    UNUSED(size);

    if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
        return (0); /* printf(".0d", 0)  no char is printed */

    if (precision > 0 && precision < length)
        padd = ' ';

    while (precision > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
        padd = '0';

    if (width > length)
    {
        for (i = 0; i < width - length; i++)
            buffer[i] = padd;

        buffer[i] = '\0';

        if (flags & FLAG_MINUS) /* Assign extra char to the left of buffer [buffer > padd] */
        {
            return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
        }
        else /* Assign extra char to the left of padding [padd > buffer] */
        {
            return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
        }
    }

    return (write(1, &buffer[ind], length));
}

/**
 * writePointer - Write a memory address
 * @buffer: Array of characters.
 * @ind: Index at which the number starts in the buffer.
 * @length: Length of the number.
 * @width: Width specifier.
 * @flags: Active flags.
 * @padd: Character representing the padding.
 * @extra_c: Character representing the extra character.
 * @padd_start: Index at which padding should start.
 *
 * Return: Number of characters written.
 */
int writePointer(char buffer[], int ind, int length,
                  int width, int flags, char padd, char extra_c, int padd_start)
{
    int i;

    if (width > length)
    {
        for (i = 3; i < width - length + 3; i++)
            buffer[i] = padd;
        buffer[i] = '\0';
        if (flags & FLAG_MINUS && padd == ' ') /* Assign extra char to the left of buffer [buffer > padd] */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
        }
        else if (!(flags & FLAG_MINUS) && padd == ' ') /* Assign extra char to the left of buffer [buffer > padd] */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
        }
        else if (!(flags & FLAG_MINUS) && padd == '0') /* Assign extra char to the left of padd [padd > buffer] */
        {
            if (extra_c)
                buffer[--padd_start] = extra_c;
            buffer[1] = '0';
            buffer[2] = 'x';
            return (write(1, &buffer[padd_start], i - padd_start) +
                    write(1, &buffer[ind], length - (1 - padd_start) - 2));
        }
    }

    buffer[--ind] = 'x';
    buffer[--ind] = '0';
    if (extra_c)
        buffer[--ind] = extra_c;
    return (write(1, &buffer[ind], BUFFER_SIZE - ind - 1));
}
