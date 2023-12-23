/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:33:56 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/23 17:06:06 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void printf_hex_prefix(t_lexer_status * lexer_status)
{
    if (lexer_status->width_char == '0')
    {
       if (lexer_status->lexer_flags.hash && lexer_status->_case_ == LOWERCASE)
            printf_write(lexer_status, "0x", 2);
       else if (lexer_status->lexer_flags.hash && lexer_status->_case_ == UPPERCASE)
            printf_write(lexer_status, "0X", 2);
    }
}

size_t hex_get_preffix_size(t_lexer_status * lexer_status, size_t l_hex_len)
{
    size_t prefix;
    prefix = 0;
   
    lexer_status->width_char = ' ';
    if (lexer_status->lexer_flags.zero && !lexer_status->precision.exist)
        lexer_status->width_char = '0';
    if (lexer_status->precision.exist && (size_t)lexer_status->precision.value > l_hex_len)
        prefix += lexer_status->precision.value - l_hex_len;
    if (lexer_status->lexer_flags.hash)
        prefix += 2;
    return (prefix);
}

	void printf_hex_write(t_lexer_status *lexer_status,
		char *l_hex_str, size_t l_hex_len)
	{
        if (lexer_status->width_char == ' ')
        {
            if (lexer_status->lexer_flags.hash && lexer_status->_case_ == LOWERCASE)
                printf_write(lexer_status, "0x", 2);
            else if (lexer_status->lexer_flags.hash && lexer_status->_case_ == UPPERCASE)
                printf_write(lexer_status, "0X", 2);
        }
        if (lexer_status->precision.exist && (size_t)lexer_status->precision.value > l_hex_len)
            printf_width(lexer_status, lexer_status->precision.value - l_hex_len, '0');
   		printf_write(lexer_status, l_hex_str, l_hex_len);
	}

