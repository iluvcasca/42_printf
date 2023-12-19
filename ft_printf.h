/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:43:04 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/19 17:26:01 by kgriset          ###   ########.fr       */
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
        FLAGS = 3,
        WIDTH = 4,
        PRECISION = 5,
        TYPE,
    }t_lexer_state ;

typedef enum e_case {
    UPPERCASE,
    LOWERCASE,
}t_case;

typedef struct s_lexer_flags
{
    unsigned int minus;
    unsigned int zero;
    unsigned int plus;
    unsigned int space;
    unsigned int hash;
    size_t i;
} t_lexer_flags;

typedef enum e_precision_exist {
                FALSE,
                TRUE,
            } t_precision_exist;

typedef struct s_precision {
    t_precision_exist exist;
                        int value;
        } t_precision;

typedef struct s_state_map { 
    t_lexer_state current_state;
    t_lexer_state next_state;
} t_state_map;

typedef struct s_lexer_status
{
        t_lexer_state lexer_state;
        t_lexer_flags lexer_flags;
        int width;
        t_precision precision;
        int return_value; 
        int printed_count;
} t_lexer_status;


int ft_printf(const char * format,...);
unsigned int isEOF (char * format, int index);
char peek(char * format, int index);
char consume(char ** format, int index);
int lexer (char ** format, va_list ap);
void lexer_string_litteral(char ** format, t_lexer_status * lexer_status);
void printf_putchar(t_lexer_status * lexer_status, void * current_char);
 void lexer_putstr(t_lexer_status * lexer_status, void * arg);
void lexer_pointer(t_lexer_status * lexer_status, void * arg);
void lexer_placeholder(char ** format, t_lexer_status * lexer_status, va_list ap);
void lexer_put_integer (t_lexer_status * lexer_status, va_list ap);
void lexer_put_unsignedinteger (t_lexer_status * lexer_status, va_list ap);
void printf_convert_hexa (unsigned int x, t_lexer_status * lexer_status, t_case _case);
void lexer_put_hexa (t_lexer_status * lexer_status, t_case _case , va_list ap);
void lexer_flags(char ** format, t_lexer_status * lexer_status);
void lexer_is_valid_flags(char ** format, t_lexer_status * lexer_status);
void    lexer_width(char ** format, t_lexer_status * lexer_status);
void lexer_precision(char ** format, t_lexer_status * lexer_status);
void lexer_atoi(char ** format, t_lexer_status * lexer_status, int * value, t_state_map state_map);
void lexer_type(char ** format, t_lexer_status * lexer_status, va_list ap);
void process_type(char ** format, t_lexer_status * lexer_status, void * arg, void (*put_type)(t_lexer_status * lexer_status, void * arg));
void lexer_type2(char ** format, t_lexer_status * lexer_status, va_list ap);
void printf_width (t_lexer_status * lexer_status, int effective_width, char filler);
void lexer_putchar (t_lexer_status * lexer_status, void * arg);
void printf_write (t_lexer_status * lexer_status, char * address, int count);
void lexer_putstr2(t_lexer_status * lexer_status, void * arg, size_t len, void * arg_cpy);
void printf_pointer_size (uintptr_t p, size_t * i);
void printf_convert_pointer (uintptr_t p, t_lexer_status * lexer_status, char * ptr_address, size_t ptr_len);
void    lexer_pointer2(t_lexer_status * lexer_status, char * ptr_str, size_t ptr_len, void * arg);
void printf_pointer_write(t_lexer_status * lexer_status, void * arg, char * ptr_str, size_t ptr_len);
	void lexer_integer(t_lexer_status *lexer_status, void *arg);
void	printf_utoa(unsigned int u, t_lexer_status *lexer_status,
		char *u_int_adress, size_t u_int_len);
void	printf_utoa_size(unsigned int u, size_t *u_int_len);
void lexer_integer2(t_lexer_status *lexer_status, char *int_str,
		size_t int_len, void *arg);
size_t integer_get_preffix_size(t_lexer_status * lexer_status, int int_value);
#endif
