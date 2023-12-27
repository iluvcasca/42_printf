/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:19:15 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/27 18:25:38 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*current_char;
	long	return_value;

	return_value = 0; // remove
	current_char = (char *)format;
	va_start(ap, format);
	return_value = lexer(&current_char, ap);
	va_end(ap);
	return (return_value);
}

int	lexer(char **format, va_list ap)
{
	t_lexer_status	lexer_status;

	lexer_status.lexer_state = STRING_LITTERAL;
	lexer_status.printed_count = 0;
	lexer_status.return_value = 0;
	while (!iseof(*format, 0))
	{
		lexer_string_litteral(format, &lexer_status);
		lexer_flags(format, &lexer_status);
		lexer_width(format, &lexer_status);
		lexer_precision(format, &lexer_status);
		lexer_type(format, &lexer_status, ap);
	}
	if (lexer_status.return_value != -1)
		lexer_status.return_value = lexer_status.printed_count;
	return (lexer_status.return_value);
}
