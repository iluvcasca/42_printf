/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lexer_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:33:34 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/09 22:34:52 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void lexer_put_integer (t_lexer_status * lexer_status, va_list ap)
{
    int i;

    i = va_arg(ap, int);
    if(!i)
    {
        lexer_putchar('0', lexer_status);
        return;
    }
    if (i < 0)
    {
        lexer_putchar('-', lexer_status);
        printf_utoa(-1 * i, lexer_status);
    }
    else
        printf_utoa(i, lexer_status);
    lexer_status->lexer_state = STRING_LITTERAL;
}

void lexer_put_unsignedinteger (t_lexer_status * lexer_status, va_list ap)
{
    unsigned int u;

    u = va_arg(ap, int);
    if (!u)
    {
        lexer_putchar('0', lexer_status);
        return;
    }
    printf_utoa(u, lexer_status);
    lexer_status->lexer_state = STRING_LITTERAL;
}

void lexer_put_hexa (t_lexer_status * lexer_status, t_case _case , va_list ap)
{
   unsigned int x;

    x = va_arg(ap, int);
    if (!x)
    {
        lexer_putchar('0', lexer_status);
        lexer_status->lexer_state = STRING_LITTERAL;
        return;
    }
    else
        printf_convert_hexa(x, lexer_status, _case);
    lexer_status->lexer_state = STRING_LITTERAL;
}
