/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lexer_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:23:22 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/29 16:51:55 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_type(char **format, t_lexer_status *lexer_status, void *arg,
		void (*put_type)(t_lexer_status *, void *))
{
	(*put_type)(lexer_status, arg);
	consume(format, lexer_status->lexer_flags.i);
}

void	printf_width(t_lexer_status *lexer_status, int effective_width,
		char filler)
{
	char	*str_width;

	if (effective_width <= 0)
		return ;
	str_width = malloc(sizeof(char) * (effective_width));
	if (!str_width)
		return ;
	ft_memset(str_width, (int)filler, (effective_width));
	printf_write(lexer_status, str_width, effective_width);
	free(str_width);
}

void	printf_write(t_lexer_status *lexer_status, char *address, size_t count)
{
	size_t	byte_read;

	byte_read = 0;
	if (count <= 0)
		return ;
	while (byte_read < count)
		byte_read += write(1, address + byte_read, count - byte_read);
	if (byte_read < count || (size_t)(INT_MAX
		- lexer_status->printed_count) < byte_read)
		lexer_status->return_value = -1;
	lexer_status->printed_count += byte_read;
}
