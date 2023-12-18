/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:19:15 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/18 15:05:45 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*current_char;

	long return_value = 0; // remove
	current_char = (char *)format;
	va_start(ap, format);
	return_value = lexer(&current_char, ap);
	va_end(ap);
	return (return_value);
}
