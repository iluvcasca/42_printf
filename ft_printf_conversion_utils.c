/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:16:36 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/27 16:01:56 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	printf_convert_pointer(uintptr_t p, t_lexer_status *lexer_status,
		char *ptr_address, size_t ptr_len)
{
	char	*table;

	table = "0123456789abcdef";
	if (p)
		printf_convert_pointer(p / 16, lexer_status, ptr_address, --ptr_len);
	else
		return ;
	ptr_address[ptr_len] = table[p % 16];
}

void	printf_pointer_size(uintptr_t p, size_t *ptr_len)
{
	if (p)
		printf_pointer_size(p / 16, ptr_len);
	else
		return ;
	(*ptr_len)++;
}

void	printf_utoa_size(unsigned int u, size_t *u_int_len)
{
	if (u)
		printf_utoa_size(u / 10, u_int_len);
	else
		return ;
	(*u_int_len)++;
}

void	printf_utoa(unsigned int u, t_lexer_status *lexer_status,
		char *u_int_address, size_t u_int_len)
{
	char	*table;

	table = "0123456789";
	if (u)
		printf_utoa(u / 10, lexer_status, u_int_address, --u_int_len);
	else
		return ;
	u_int_address[u_int_len] = table[u % 10];
}
