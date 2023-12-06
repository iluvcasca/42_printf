/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:43:04 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/06 17:24:12 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
int ft_printf(const char * format,...);
unsigned int isEOF (char * format, int index);
char peek(char ** format, int index);
char consume(char ** format, int index);
int lexer (char ** format, va_list ap);
typedef enum lexer_state {
    ERROR = -1,
    STRING_LITTERAL = 1,
    FORMAT_PlACEHOLDER = 2,
} t_lexer_state;
#endif
