/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:16:36 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/09 22:36:54 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void printf_convert_pointer (uintptr_t p, t_lexer_status * lexer_status)
{
    char * table;

    table = "0123456789abcdef";
    if (p)
        printf_convert_pointer(p/16, lexer_status);
    else
        return;
    lexer_putchar (table[p % 16], lexer_status);
}

void	printf_utoa(unsigned int u, t_lexer_status * lexer_status)
{
    char * table;

    table = "0123456789";
    if (u)
        printf_utoa(u/10, lexer_status);
    else
        return;
    lexer_putchar(table[u%10], lexer_status);
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
    lexer_putchar (table[x % 16], lexer_status);
}
