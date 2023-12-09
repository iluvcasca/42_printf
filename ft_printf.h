/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:43:04 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/09 22:25:36 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>
#include "libft.h"
#include <stdlib.h>
typedef enum e_lexer_state {
        ERROR = -1,
        STRING_LITTERAL = 1,
        FORMAT_PlACEHOLDER = 2,
    }t_lexer_state ;

typedef enum e_case {
    UPPERCASE,
    LOWERCASE,
}t_case;

typedef struct s_lexer_status
{
        t_lexer_state lexer_state;
        int return_value; 
        int printed_count;
} t_lexer_status;
int ft_printf(const char * format,...);
unsigned int isEOF (char * format, int index);
char peek(char ** format, int index);
char consume(char ** format, int index);
int lexer (char ** format, va_list ap);
void lexer_string(char ** format, t_lexer_status * lexer_status);
void lexer_putchar(char current_char, t_lexer_status * lexer_status);
void lexer_putstr(t_lexer_status * lexer_status, va_list ap);
void lexer_pointer(t_lexer_status * lexer_status, va_list ap);
void printf_convert_pointer (uintptr_t p, t_lexer_status * lexer_status);
void lexer_placeholder(char ** format, t_lexer_status * lexer_status, va_list ap);
void lexer_put_integer (t_lexer_status * lexer_status, va_list ap);
void lexer_put_unsignedinteger (t_lexer_status * lexer_status, va_list ap);
void	printf_utoa(unsigned int u, t_lexer_status * lexer_status);
void printf_convert_hexa (unsigned int x, t_lexer_status * lexer_status, t_case _case);
void lexer_put_hexa (t_lexer_status * lexer_status, t_case _case , va_list ap);
#endif
