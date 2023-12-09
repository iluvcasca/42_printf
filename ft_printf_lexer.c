/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:21:16 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/09 22:27:17 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
    if (lexer_status.return_value != -1)
        lexer_status.return_value = lexer_status.printed_count;
    return (lexer_status.return_value);
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
            else if (current_char == 'x')
                lexer_put_hexa(lexer_status, LOWERCASE, ap);
            else if (current_char == 'X')
                lexer_put_hexa(lexer_status, UPPERCASE, ap);

            consume(format, 0);
        }
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
