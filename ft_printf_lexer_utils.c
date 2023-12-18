/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lexer_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:25:53 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/18 15:21:11 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	peek(char *format, int index)
{
	return (*(format + index));
}

unsigned int	isEOF(char *format, int index)
{
	if (*(format + index) == 0)
		return (1);
	return (0);
}

char	consume(char **format, int index)
{
	char char_to_return ;
	char_to_return = (*(*format + index));
	*format += (index + 1);
	return (char_to_return);
}

void	printf_putchar(t_lexer_status *lexer_status, void *current_char)
{
	int	byte_read;

	byte_read = write(1, current_char, 1);
	if (lexer_status->printed_count == INT_MAX || byte_read != 1)
		lexer_status->return_value = -1;
	lexer_status->printed_count++;
}
