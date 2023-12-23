/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:33:56 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/24 00:27:21 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void printf_hex_prefix(t_lexer_status * lexer_status, int * offset)
{
    (*offset) = 0;
    if (lexer_status->width_char == '0'&& lexer_status->lexer_flags.hash)
    {
       if (lexer_status->_case_ == LOWERCASE)
            printf_write(lexer_status, "0x", 2);
       else if (lexer_status->_case_ == UPPERCASE)
            printf_write(lexer_status, "0X", 2);
       (*offset) = 2;
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
    return (prefix);
}

	void printf_hex_write(t_lexer_status *lexer_status,
		char *l_hex_str, size_t l_hex_len)
	{
        // if (lexer_status->width_char == ' ')
        // {
        //     if (lexer_status->lexer_flags.hash && lexer_status->_case_ == LOWERCASE)
        //         printf_write(lexer_status, "0x", 2);
        //     else if (lexer_status->lexer_flags.hash && lexer_status->_case_ == UPPERCASE)
        //         printf_write(lexer_status, "0X", 2);
        // }
        if (lexer_status->precision.exist && (size_t)lexer_status->precision.value > l_hex_len)
            printf_width(lexer_status, lexer_status->precision.value - l_hex_len, '0');
        else if (lexer_status->precision.exist && (size_t)lexer_status->precision.value < l_hex_len)
            l_hex_len = lexer_status->precision.value;
   		printf_write(lexer_status, l_hex_str, l_hex_len);
	}

void	printf_hex_size_wrapper(t_lexer_status * lexer_status, unsigned int x, size_t *hex_len)
{
   if (lexer_status->lexer_flags.hash)
        (*hex_len) += 2;
   if (x)
        printf_hex_size(x, hex_len);
   else
        (*hex_len) += 1;
}

void	printf_convert_hexa_wrapper(unsigned int x, t_lexer_status *lexer_status, char * hex_address, size_t hex_len)
{
    char * hash; 
    int offset;

    hash = "xX";
    offset = 0;
    if (lexer_status->lexer_flags.hash)
    {
        hex_address[0] = '0';
        hex_address[1] = hash[lexer_status->_case_];
        offset += 2;
    }
    if (!x)
        hex_address[hex_len-1] = '0'; 
    else
        printf_convert_hexa(x, lexer_status, hex_address + offset, hex_len - offset);
}
