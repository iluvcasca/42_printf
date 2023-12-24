/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_Uhex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:32:01 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/23 17:09:42 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

	void lexer_Uhex(t_lexer_status *lexer_status, void *arg)
{
    size_t U_hex_len;
    char *U_hex_str;

    U_hex_len = 0;
    lexer_status->_case_ = UPPERCASE;
    if (lexer_status->lexer_flags.plus
                || lexer_status->lexer_flags.space)
        lexer_status->return_value = -1;
    if (*((unsigned int *)arg) == 0 && ++U_hex_len) 
        U_hex_str = "0";
    else
    {
        printf_hex_size((*((unsigned int *)arg)), &U_hex_len); 
        U_hex_str = malloc(sizeof(char) * (U_hex_len));
        if (!U_hex_str)
            return;
        printf_convert_hexa((*((unsigned int *)arg)), lexer_status, U_hex_str, U_hex_len);
    }
    lexer_Uhex2(lexer_status, U_hex_str, U_hex_len, arg);
}

	void lexer_Uhex2(t_lexer_status *lexer_status, char *U_hex_str,
		size_t U_hex_len, void *arg)
	{
		size_t prefix;

		prefix = hex_get_preffix_size(lexer_status, U_hex_len);
		if (lexer_status->width)
		{
			if (lexer_status->lexer_flags.minus)
        {
				printf_hex_write(lexer_status, U_hex_str, U_hex_len);
                printf_width(lexer_status, lexer_status->width - U_hex_len - prefix,
				' ');
        }
			if (!lexer_status->lexer_flags.minus)
        {
                printf_hex_prefix(lexer_status);
	            printf_width(lexer_status, lexer_status->width - U_hex_len - prefix,
				lexer_status->width_char);
				printf_hex_write(lexer_status, U_hex_str, U_hex_len);
        }
		}
		else
			printf_hex_write(lexer_status, U_hex_str, U_hex_len);
        lexer_Uhex3(U_hex_str, arg);
	}

void lexer_Uhex3(char * U_hex_str, void * arg)
{
    if (*((unsigned int *)arg))
        free(U_hex_str);
}
