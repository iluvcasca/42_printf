/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:21:16 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/27 18:25:38 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	lexer_string_litteral(char **format, t_lexer_status *lexer_status)
{
	char	current_char;

	while (lexer_status->lexer_state == STRING_LITTERAL && !iseof(*format, 0))
	{
		current_char = peek(*format, 0);
		if (current_char == '%')
			lexer_status->lexer_state = FLAGS;
		else
		{
			printf_putchar(lexer_status, &current_char);
			// optimisation to be made with only a single call to write
			consume(format, 0);
		}
	}
}

void	lexer_flags(char **format, t_lexer_status *lexer_status)
{
	char	current_char;

	lexer_status->lexer_flags = (t_lexer_flags){};
	while (lexer_status->lexer_state == FLAGS /*&& !iseof(*format,
			lexer_status->lexer_flags.i + 1)*/)
	{
		current_char = peek(*format, ++(lexer_status->lexer_flags.i));
		if (current_char == '-')
			lexer_status->lexer_flags.minus++;
		else if (current_char == '0')
			lexer_status->lexer_flags.zero++;
		else if (current_char == '#')
			lexer_status->lexer_flags.hash++;
		else if (current_char == ' ')
			lexer_status->lexer_flags.space++;
		else if (current_char == '+')
			lexer_status->lexer_flags.plus++;
		else
			lexer_status->lexer_state = WIDTH;
	}
}

void	lexer_width(char **format, t_lexer_status *lexer_status)
{
	t_state_map	state_map;

	lexer_status->width = 0;
	if (lexer_status->lexer_state == WIDTH)
	{
		state_map.current_state = WIDTH;
		state_map.next_state = PRECISION;
		lexer_atoi(format, lexer_status, &(lexer_status->width), state_map);
	}
	lexer_status->precision = (t_precision){0};
}

void	lexer_precision(char **format, t_lexer_status *lexer_status)
{
	t_state_map	state_map;

	if (lexer_status->lexer_state == PRECISION && peek(*format,
			lexer_status->lexer_flags.i) == '.')
	{
		lexer_status->precision.exist = TRUE;
		(lexer_status->lexer_flags.i)++;
		state_map.current_state = PRECISION;
		state_map.next_state = TYPE;
		lexer_atoi(format, lexer_status, &(lexer_status->precision.value),
			state_map);
	}
	else if (lexer_status->lexer_state == PRECISION)
		lexer_status->lexer_state = TYPE;
}

void	lexer_type(char **format, t_lexer_status *lexer_status, va_list ap)
{
	char	current_char;

	current_char = peek(*format, lexer_status->lexer_flags.i);
	if (lexer_status->lexer_state == TYPE /* && !iseof(*format,
			lexer_status->lexer_flags.i)*/)
	{
		if (current_char == '%')
			process_type(format, lexer_status, &current_char, printf_putchar);
		else if (current_char == 'c')
			process_type(format, lexer_status, &((int){(va_arg(ap, int))}),
				lexer_putchar);
		else if (current_char == 's')
			process_type(format, lexer_status, va_arg(ap, char *),
				lexer_putstr);
		else if (current_char == 'p')
			process_type(format, lexer_status, va_arg(ap, void *),
				lexer_pointer);
		else
			lexer_type2(format, lexer_status, ap);
	}
	lexer_status->lexer_state = STRING_LITTERAL;
}
