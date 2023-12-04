/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:19:15 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/04 21:00:56 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int ft_printf(const char * format,...)
{
    va_list ap;
    char * current_char;

    current_char = (char *)format;
    va_start(ap, format);
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
