/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:19:15 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/08 19:15:01 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int ft_printf(const char * format,...)
{
    va_list ap;
    char * current_char;

    current_char = (char *)format;
    va_start(ap, format);
    lexer(&current_char, ap);
    va_end(ap);

    return (1);
}

char peek(char ** format, int index)
{
    return (**(format + index));
}

unsigned int isEOF (char * format, int index)
{
     if (*(format + index) == 0)   
        return (1);
    return (0);
}

char consume(char ** format, int index)
{
    char char_to_return; 

    char_to_return = *(*format + index);
    *format += (index + 1);
    return (char_to_return);
}

void lexer_putchar(char current_char, t_lexer_status * lexer_status)
{
    write(1, &current_char, 1);
    if (lexer_status->printed_count == INT_MAX)
        lexer_status->return_value = -1;
    lexer_status->printed_count++;
}

void lexer_putstr(t_lexer_status * lexer_status, va_list ap)
{
    size_t i;
    char * str;

    i = 0;
    str = va_arg(ap, char *); 
    if (str == NULL)
        str = "(null)";
    while (str[i])
        lexer_putchar(str[i++], lexer_status);
    lexer_status->lexer_state = STRING_LITTERAL;
}

void lexer_pointer(t_lexer_status * lexer_status, va_list ap)
{ 
    uintptr_t p;
    char * table;
    size_t i;

    i = 0;
    table = "(nil)"; 
    p = (uintptr_t)va_arg(ap, void *);
    if (!p)
    {
        while (table[i])
            lexer_putchar (table[i++], lexer_status);
    }
    else
    {
        lexer_putchar('0', lexer_status);
        lexer_putchar('x', lexer_status);
        printf_convert_base(p, lexer_status);  
    }
}

void printf_convert_base (uintptr_t p, t_lexer_status * lexer_status)
{
    char * table;

    table = "0123456789abcdef";
    if (p)
        printf_convert_base(p/16, lexer_status);
    else
        return;
    lexer_putchar (table[p % 16], lexer_status);
}

void lexer_placeholder(char ** format, t_lexer_status * lexer_status, va_list ap)
{
    char current_char;
    while(lexer_status->lexer_state == FORMAT_PlACEHOLDER && !isEOF(*format, 0)) 
        {
            current_char = peek(format, 0);             
            if (current_char == '%')
            {
                lexer_status->lexer_state = STRING_LITTERAL;
                lexer_putchar(current_char, lexer_status);
            }
            else if(current_char == 'p')
            {
                lexer_status->lexer_state = STRING_LITTERAL;
                lexer_pointer(lexer_status, ap);
            }
            consume(format, 0);
        }
}

void lexer_string(char ** format, t_lexer_status * lexer_status)
{
    char current_char;
    while(lexer_status->lexer_state == STRING_LITTERAL && !isEOF(*format, 0)) 
        {
            current_char = peek(format, 0);             
            if (current_char == '%')
                lexer_status->lexer_state = FORMAT_PlACEHOLDER;
            else
                lexer_putchar(current_char, lexer_status);
            consume(format, 0);
        }
}

int lexer (char ** format, va_list ap)
{
    static t_lexer_status lexer_status;
    char current_char; 

    lexer_status.lexer_state = STRING_LITTERAL;
    while(!isEOF(*format,0))
    {
        lexer_string(format, &lexer_status);
        lexer_placeholder(format, &lexer_status, ap);
    }
    return (lexer_status.return_value);
}
