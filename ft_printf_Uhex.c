/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_Uhex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:32:01 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/24 12:33:15 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

	void lexer_Uhex(t_lexer_status *lexer_status, void *arg)
{
    size_t l_hex_len;
    char *l_hex_str;

    l_hex_len = 0;
    lexer_status->_case_ = UPPERCASE;
    if (lexer_status->lexer_flags.plus
                || lexer_status->lexer_flags.space)
        lexer_status->return_value = -1;
    if (*((unsigned int *)arg) == 0 && ++l_hex_len) 
        l_hex_str = "0";
    else
    {
        printf_hex_size((*((unsigned int *)arg)), &l_hex_len); 
        l_hex_str = malloc(sizeof(char) * (l_hex_len));
        if (!l_hex_str)
            return;
        printf_convert_hexa((*((unsigned int *)arg)), lexer_status, l_hex_str, l_hex_len);
    }
    lexer_Uhex2(lexer_status, l_hex_str, l_hex_len, arg);
}

	void lexer_Uhex2(t_lexer_status *lexer_status, char *l_hex_str,
		size_t l_hex_len, void *arg)
	{
		size_t prefix;

		prefix = hex_get_preffix_size(lexer_status, &l_hex_len, *((unsigned int *)arg));
		if (lexer_status->width)
		{
			if (lexer_status->lexer_flags.minus)
        {
				printf_hex_write(lexer_status, l_hex_str, l_hex_len);
                printf_width(lexer_status, lexer_status->width - l_hex_len - prefix,
				' ');
        }
			if (!lexer_status->lexer_flags.minus)
        {
                printf_hex_prefix(lexer_status, *((unsigned int *)arg));
	            printf_width(lexer_status, lexer_status->width - l_hex_len - prefix,
				lexer_status->width_char);
				printf_hex_write(lexer_status, l_hex_str, l_hex_len);
        }
		}
		else
        {
            printf_hex_prefix(lexer_status, *((unsigned int *)arg));
			printf_hex_write(lexer_status, l_hex_str, l_hex_len);
        }
        lexer_Uhex3(l_hex_str, arg);
	}

void lexer_Uhex3(char * l_hex_str, void * arg)
{
    if (*((unsigned int *)arg))
        free(l_hex_str);
}
