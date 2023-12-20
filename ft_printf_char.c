/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:27:09 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/20 22:27:51 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

	void lexer_putchar(t_lexer_status *lexer_status, void *arg)
	{
		if (lexer_status->lexer_flags.hash || lexer_status->lexer_flags.plus
			|| lexer_status->lexer_flags.zero
			|| lexer_status->lexer_flags.space)
			lexer_status->return_value = -1;
		if (lexer_status->width)
		{
			if (lexer_status->lexer_flags.minus)
				printf_putchar(lexer_status, arg);
			printf_width(lexer_status, lexer_status->width - 1, ' ');
			if (!lexer_status->lexer_flags.minus)
				printf_putchar(lexer_status, arg);
		}
		else
			printf_putchar(lexer_status, arg);
	}
