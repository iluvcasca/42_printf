/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:21:16 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/13 17:50:07 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int lexer (char ** format, va_list ap)
{
    t_lexer_status lexer_status;
    char current_char; 

    lexer_status.lexer_state = STRING_LITTERAL;
    lexer_status.printed_count = 0;
    lexer_status.return_value = 0;
    while(!isEOF(*format,0))
    {
        lexer_string(format, &lexer_status);
        lexer_placeholder(format, &lexer_status, ap);
    }
    if (lexer_status.return_value != -1)
        lexer_status.return_value = lexer_status.printed_count;
    return (lexer_status.return_value);
}

void lexer_string(char ** format, t_lexer_status * lexer_status)
{
    char current_char;
    while(lexer_status->lexer_state == STRING_LITTERAL && !isEOF(*format, 0)) 
        {
            current_char = peek(*format, 0);             
            if (current_char == '%')
                lexer_status->lexer_state = FORMAT_PlACEHOLDER;
            else
            {
                lexer_putchar(current_char, lexer_status);
                consume(format, 0);
            }
        }
}

void lexer_placeholder(char ** format, t_lexer_status * lexer_status, va_list ap)
{
    char current_char;
    while(lexer_status->lexer_state == FORMAT_PlACEHOLDER && !isEOF(*format, 1)) // if ?
        {
            current_char = peek(*format, 1);             
            // if (current_char == '%')
            // {
            //     lexer_putchar(current_char, lexer_status);
            //     lexer_status->lexer_state = STRING_LITTERAL;
            //     consume(format, 1); // ATTENTION
            // }
            // else
            // {
                lexer_status->lexer_state = FLAGS;
                lexer_flags(format, lexer_status, ap);
            // }
        }
}

void lexer_flags(char ** format, t_lexer_status * lexer_status, va_list ap)
{
    char current_char;
    size_t i;

    lexer_status->lexer_flags = (t_lexer_flags){};
    i = 0;

    while(lexer_status->lexer_state == FLAGS && !isEOF(*format, i + 1))
    {
        current_char = peek(*format, ++i); 
        if (current_char == '-')
            lexer_status->lexer_flags.minus++;
        else if (current_char == '0')
            lexer_status->lexer_flags.zero++;
        else if (current_char == '#')
                lexer_status->lexer_flags.hash++;
        else if (current_char == ' ')
                lexer_status->lexer_flags.space++;
        else if (current_char == '+')
                lexer_status->lexer_flags.plus++;
        else
            lexer_status->lexer_state = WIDTH;
    }
    lexer_width(i, format, lexer_status, ap);
}

void lexer_width(int i, char ** format, t_lexer_status * lexer_status, va_list ap)
{
    char current_char;

    lexer_status->width = 0;     
    while (lexer_status->lexer_state == WIDTH && !isEOF(*format, i))
    {
        current_char = peek(*format, i);
        if (lexer_status->width >= INT_MAX / 10 && current_char - '0' >= 8 && ft_isdigit(current_char))  
        {
            lexer_status->width = 0;
            lexer_status->lexer_state = PRECISION;
            lexer_status->return_value = -1;
        }
        else if (ft_isdigit(current_char))
        {
            lexer_status->width = lexer_status->width * 10 + current_char - '0';
            i++;
        }
        else 
            lexer_status->lexer_state = PRECISION;  
    }
    lexer_status->precision = (t_precision){0};
    lexer_precision(i, format, lexer_status, ap);
}

void lexer_precision(int i, char ** format, t_lexer_status * lexer_status, va_list ap)
{
    char current_char; 

    current_char = peek(*format, i);

    if (current_char == '.')
        lexer_status->precision.t_precision_exist = TRUE;
    else 
        lexer_status->lexer_state = TYPE;
    while (lexer_status->lexer_state == PRECISION && !isEOF(*format, i))
    {
        if (lexer_status->precision.value >= INT_MAX / 10 && current_char - '0' >= 8 && ft_isdigit(current_char))  
        {
            lexer_status->precision.value = 0;
            lexer_status->lexer_state = TYPE;
            lexer_status->return_value = -1;
        }
        else if (ft_isdigit(current_char))
        {
            lexer_status->precision.value = lexer_status->precision.value * 10 + current_char - '0';
            i++;
        }
        else 
            lexer_status->lexer_state = TYPE;  
    }
    lexer_type(i, format, lexer_status, ap);
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
        printf_convert_pointer(p, lexer_status);  
    }
    lexer_status->lexer_state = STRING_LITTERAL;
}


