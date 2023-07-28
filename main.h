#ifndef PRINTF_MAIN_H
#define PRINTF_MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED_PARAM(x) (void)(x)
#define BUFFER_SIZE 1024

/* FLAGS */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* SIZES */
#define SIZE_LONG 2
#define SIZE_SHORT 1

/**
 * struct format_specifier - Struct to define a format specifier and its function.
 * @specifier: The format specifier character.
 * @function: The function pointer associated with the format specifier.
 */
struct format_specifier
{
    char specifier;
    int (*function)(va_list, char[], int, int, int, int);
};

typedef struct format_specifier format_specifier_t;

/**
 * _printf - Custom implementation of printf function.
 * @format: The formatted string containing the arguments to be printed.
 * @...: The variable number of arguments to be printed based on the format.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...);

/* Width handler */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[], int flags, int width, int precision, int size);
int write_num(int ind, char buffer[], int flags, int width, int precision, int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size);

/* Functions to handle other specifiers */
int get_flags(const char *format_str, int *index_ptr);
int get_width(const char *format_str, int *index_ptr, va_list arg_list);
int get_precision(const char *format_str, int *index_ptr, va_list arg_list);
int get_size(const char *format_str, int *index_ptr);

/* Function to print string in reverse */
int print_reverse(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Function to print a string in rot13 */
int print_rot13string(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Function to print non-printable characters */
int print_non_printable(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Function to print memory address */
int print_pointer(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Functions to print numbers */
int print_int(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_binary(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_unsigned(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_octal(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_hexadecimal(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_hex_upper(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Funtions to print characters and strings */
int print_char(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_string(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_percent(va_list args, char buffer[], int flags, int width, int precision, int size);

/* HELPER FUNCTIONS */
int is_printable_char(char c);
int append_hex_code(char c, char buffer[], int index);
int append_hex_code(char c, char buffer[], int index);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* PRINTF_MAIN_H */
