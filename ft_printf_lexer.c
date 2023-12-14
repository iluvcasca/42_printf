/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:21:16 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/14 18:35:54 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int lexer (char ** format, va_list ap)
{
    t_lexer_status lexer_status;

    lexer_status.lexer_state = STRING_LITTERAL;
    lexer_status.printed_count = 0;
    lexer_status.return_value = 0;
    while(!isEOF(*format,0))
    {
        lexer_string(format, &lexer_status);
        // lexer_placeholder(format, &lexer_status, ap);
        lexer_flags(format, &lexer_status);
        lexer_width(format, &lexer_status);
        lexer_precision(format, &lexer_status);
        lexer_type(format, &lexer_status, ap);
        
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
                lexer_status->lexer_state = FLAGS;
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
                // lexer_flags(format, lexer_status, ap);
            // }
        }
}

void lexer_flags(char ** format, t_lexer_status * lexer_status)
{
    char current_char;

    lexer_status->lexer_flags = (t_lexer_flags){};

    while(lexer_status->lexer_state == FLAGS && !isEOF(*format, lexer_status->lexer_flags.i + 1))
    {
        current_char = peek(*format, ++(lexer_status->lexer_flags.i)); 
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
}

void lexer_width(char ** format, t_lexer_status * lexer_status)
{
    t_state_map state_map;

    lexer_status->width = 0;     

    if (lexer_status->lexer_state == WIDTH)
    {
        state_map.current_state = WIDTH;
        state_map.next_state = PRECISION;
        lexer_atoi(format, lexer_status, &(lexer_status->width), state_map);
    }
    lexer_status->precision = (t_precision){0};
}

void lexer_atoi(char ** format, t_lexer_status * lexer_status, int * value, t_state_map state_map)
{
    char current_char;

    while (lexer_status->lexer_state == state_map.current_state && !isEOF(*format, lexer_status->lexer_flags.i))
    {
        current_char = peek(*format, lexer_status->lexer_flags.i);
        if ((*value) >= INT_MAX / 10 && current_char - '0' >= 8 && ft_isdigit(current_char))  
        {
            (*value) = 0;
            lexer_status->lexer_state = state_map.next_state;
            lexer_status->return_value = -1;
            (lexer_status->lexer_flags.i)++;
        }
        else if (ft_isdigit(current_char))
        {
            (*value) = (*value) * 10 + current_char - '0';
            (lexer_status->lexer_flags.i)++;
        }
        else 
            lexer_status->lexer_state = state_map.next_state;  
    }   
}

void lexer_precision(char ** format, t_lexer_status * lexer_status)
{
    t_state_map state_map;

    if (peek(*format, lexer_status->lexer_flags.i) == '.')
    {
        lexer_status->precision.precision_exist = TRUE;
        (lexer_status->lexer_flags.i)++;
        state_map.current_state = PRECISION; 
        state_map.next_state = TYPE;
        lexer_atoi(format, lexer_status, &(lexer_status->precision.value), state_map);
    }
    else 
        lexer_status->lexer_state = TYPE;
}

void lexer_type(char ** format, t_lexer_status * lexer_status, va_list ap)
{
    
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
