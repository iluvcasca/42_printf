/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:16:36 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/17 16:31:27 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void printf_convert_pointer (uintptr_t p, t_lexer_status * lexer_status, char * ptr_adress, size_t ptr_len)
{
    char * table;

    table = "0123456789abcdef";
    if (p)
        printf_convert_pointer(p/16, lexer_status, ptr_adress, --ptr_len);
    else
        return;
    ptr_adress[ptr_len] = table[p % 16];
}

void printf_pointer_size (uintptr_t p, size_t * i)
{
    if (p)
        printf_pointer_size(p/16, i);
    else
        return;
    (*i)++;
}

void	printf_utoa(unsigned int u, t_lexer_status * lexer_status)
{
    char * table;

    table = "0123456789";
    if (u)
        printf_utoa(u/10, lexer_status);
    else
        return;
    printf_putchar(lexer_status, &table[u%10]);
}

void printf_convert_hexa (unsigned int x, t_lexer_status * lexer_status, t_case _case)
{
    char * table;

    if (_case == LOWERCASE)
        table = "0123456789abcdef";
    else
        table = "0123456789ABCDEF";
    if (x)
        printf_convert_hexa(x/16, lexer_status, _case);
    else
        return;
    printf_putchar (lexer_status, &table[x % 16]);
}
