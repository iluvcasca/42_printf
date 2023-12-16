/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:21:16 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/16 18:51:53 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// la plupars des isEOF ne serve a rien
#include "ft_printf.h"
#include "libft.h"

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
                printf_putchar(lexer_status, &current_char);
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
            //     printf_putchar(current_char, lexer_status);
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

    while(lexer_status->lexer_state == FLAGS /*&& !isEOF(*format, lexer_status->lexer_flags.i + 1)*/)
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

    while (lexer_status->lexer_state == state_map.current_state/* && !isEOF(*format, lexer_status->lexer_flags.i)*/)
    {
        current_char = peek(*format, lexer_status->lexer_flags.i);
        if (ft_isdigit(current_char) && (*value) >= INT_MAX / 10 && current_char - '0' >= 8)  
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

    if (lexer_status->lexer_state == PRECISION && peek(*format, lexer_status->lexer_flags.i) == '.')
    {
        lexer_status->precision.precision_exist = TRUE;
        (lexer_status->lexer_flags.i)++;
        state_map.current_state = PRECISION; 
        state_map.next_state = TYPE;
        lexer_atoi(format, lexer_status, &(lexer_status->precision.value), state_map);
    }
    else if (lexer_status->lexer_state == PRECISION) 
        lexer_status->lexer_state = TYPE;
}

void lexer_type(char ** format, t_lexer_status * lexer_status, va_list ap)
{
    char current_char;

    current_char = peek(*format, lexer_status->lexer_flags.i);
    if (lexer_status->lexer_state == TYPE/* && !isEOF(*format, lexer_status->lexer_flags.i)*/)
    {
        if (current_char == '%')
            process_type(format, lexer_status, &current_char, printf_putchar);
        else if (current_char == 'c')
            process_type(format, lexer_status, &((char){(va_arg(ap, int))}), lexer_putchar);
        else if (current_char == 's')
            process_type(format, lexer_status, (va_arg(ap, char *)), printf_putchar);
        // else if (current_char == 'p')
        //     process_type(format, lexer_status, &((uintptr_t){(uintptr_t)va_arg(ap, void *)}), lexer_pointer);
        // lexer_type2(format ,lexer_status, ap);
        else
        {
            printf_putchar(lexer_status, &((char){'%'}));
            consume(format, 0);
        }
    }
    lexer_status->lexer_state = STRING_LITTERAL; 
}

// void lexer_type2(char ** format, t_lexer_status * lexer_status, va_list ap)
// {
//     char current_char;
//
//     current_char = peek(*format, lexer_status->lexer_flags.i);
//     if (current_char == 'd' || current_char == 'i')
//         process_type(format, lexer_status, &current_char, lexer_put_integer);
//     else if (current_char == 'u')
//         process_type(format, lexer_status, &((char){(va_arg(ap, int))}), lexer_put_unsignedinteger);
//     else if (current_char == 'x')
//         process_type(format, lexer_status, (va_arg(ap, char *)), printf_putchar);
//     else if (current_char == 'X')
//         process_type(format, lexer_status, &((uintptr_t){(uintptr_t)va_arg(ap, void *)}), lexer_pointer);
//     // lexer_type2(format ,lexer_status, ap);
// }

void process_type(char ** format, t_lexer_status * lexer_status, void * arg, void (*put_type)(t_lexer_status *, void *))
{
    (*put_type)(lexer_status, arg); 
    consume(format, lexer_status->lexer_flags.i);
}

void lexer_putchar (t_lexer_status * lexer_status, void * arg)
{
    arg = (char *)arg;
    if (lexer_status->lexer_flags.hash 
        || lexer_status->lexer_flags.plus || lexer_status->lexer_flags.zero || lexer_status->lexer_flags.space) 
        lexer_status->return_value = -1;
    if (lexer_status->width)
    {
        if (lexer_status->lexer_flags.minus)
            printf_putchar(lexer_status, arg);
        printf_width(lexer_status, lexer_status->width - 1, ' ');
        if (!lexer_status->lexer_flags.minus)
            printf_putchar(lexer_status, arg);
    }
}

void printf_width (t_lexer_status * lexer_status, int effective_width, char filler)
{
    char * str_width;

    str_width = malloc(sizeof(char)*(effective_width));
    if (!str_width)
        return;
    ft_memset(str_width, (int)filler, (effective_width));
    lexer_status->printed_count += effective_width;
    write(1, str_width, effective_width);
    free(str_width);
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
        printf_putchar(lexer_status, &str[i++]);
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
            printf_putchar (lexer_status, &table[i++]);
    }
    else
    {
        printf_putchar(lexer_status, &((char){'0'}) );
        printf_putchar(lexer_status, &((char){'x'}) );
        printf_convert_pointer(p, lexer_status);  
    }
    lexer_status->lexer_state = STRING_LITTERAL;
}
