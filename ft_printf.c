/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:19:15 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/06 17:26:43 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int lexer (char ** format, va_list ap)
{
    static t_lexer_state lexer_state;
    char current_char; 

    lexer_state = STRING_LITTERAL;
    while(!isEOF(*format,0))
    {
        while(lexer_state == STRING_LITTERAL && !isEOF(*format, 0)) 
        {
            current_char = peek(format, 0);             
            if (current_char == '%')
                lexer_state = FORMAT_PlACEHOLDER;
            else
                write(1, &current_char, 1);
            consume(format, 0);
        }
    }
    return (lexer_state);
}
