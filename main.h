#ifndef MAIN_H
#define MAIN_H


#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>


#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/*MACRO FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* MACRO SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct operator
 *
 * @fmt: The format specifier
 * @fn: The function associated with it
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - Struct op
 * @fmt: The format specifier
 * @fm_t: The function associated with
 */
typedef struct fmt fmt_t;

/* MAIN FUNCTION */
int _printf(const char *format, ...);

/****************** PRINT FUNCTIONS ******************/

/* Print chars and strings */
int print_char(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size);

/*These functions handle the Printing of  numbers */
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_int(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexa(va_list types, char map_to[], char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Funtion to print non-printaable characters */
int print_non_printable(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Function to print  Print memory address */
int print_pointer(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Handle other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/* Function to  print a string in reverse */
int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Print a string in rot 13 format  */
int print_rot13string(va_list types, char buffer[], int flags, int width, int precision, int size);

/****************** HELPER FUNCTIONS ******************/
int is_digit(char);
int append_hexa_code(char, char[], int);
long int convert_size_unsgnd(unsigned long int num, int size);
int is_printable(char);
long int convert_size_number(long int num, int size);
#endif /* MAIN_H */
