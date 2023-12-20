/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:21:16 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/20 19:38:36 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	lexer(char **format, va_list ap)
{
	t_lexer_status	lexer_status;

	lexer_status.lexer_state = STRING_LITTERAL;
	lexer_status.printed_count = 0;
	lexer_status.return_value = 0;
	while (!isEOF(*format, 0))
	{
		lexer_string_litteral(format, &lexer_status);
		// lexer_placeholder(format, &lexer_status, ap);
		lexer_flags(format, &lexer_status);
		lexer_width(format, &lexer_status);
		lexer_precision(format, &lexer_status);
		lexer_type(format, &lexer_status, ap);
	}
	if (lexer_status.return_value != -1)
		lexer_status.return_value = lexer_status.printed_count;
	return (lexer_status.return_value);
}

void	lexer_string_litteral(char **format, t_lexer_status *lexer_status)
{
	char	current_char;

	while (lexer_status->lexer_state == STRING_LITTERAL && !isEOF(*format, 0))
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
		char current_char;

		lexer_status->lexer_flags = (t_lexer_flags){};
		while (lexer_status->lexer_state == FLAGS /*&& !isEOF(*format,
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

	void lexer_width(char **format, t_lexer_status *lexer_status)
	{
		t_state_map state_map;

		lexer_status->width = 0;
		if (lexer_status->lexer_state == WIDTH)
		{
			state_map.current_state = WIDTH;
			state_map.next_state = PRECISION;
			lexer_atoi(format, lexer_status, &(lexer_status->width), state_map);
		}
		lexer_status->precision = (t_precision){0};
	}

	void lexer_atoi(char **format, t_lexer_status *lexer_status, int *value,
		t_state_map state_map)
	{
		char current_char;

		while (lexer_status->lexer_state == state_map.current_state /*
		&& !isEOF(*format, lexer_status->lexer_flags.i)*/)
		{
			current_char = peek(*format, lexer_status->lexer_flags.i);
			if (ft_isdigit(current_char) && (*value) >= INT_MAX / 10
				&& current_char - '0' >= 8)
			{
				(*value) = 0;
				lexer_status->lexer_state = state_map.next_state;
				lexer_status->return_value = -1;
				(lexer_status->lexer_flags.i)++;
			}
			else if (ft_isdigit(current_char))
			{
				(*value) = (*value) * 10 + current_char - '0';
				(lexer_status->lexer_flags.i)++;
			}
			else
				lexer_status->lexer_state = state_map.next_state;
		}
	}

	void lexer_precision(char **format, t_lexer_status *lexer_status)
	{
		t_state_map state_map;

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

	void lexer_type(char **format, t_lexer_status *lexer_status, va_list ap)
	{
		char current_char;

		current_char = peek(*format, lexer_status->lexer_flags.i);
		if (lexer_status->lexer_state == TYPE /* && !isEOF(*format,
			lexer_status->lexer_flags.i)*/)
		{
            if (current_char == '%')
                process_type(format, lexer_status, &current_char,
                    printf_putchar);
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
			    lexer_type2(format ,lexer_status, ap);
		}
		lexer_status->lexer_state = STRING_LITTERAL;
	}

	 void lexer_type2(char ** format, t_lexer_status * lexer_status,
	 va_list ap)
	 {
        char current_char;

		current_char = peek(*format, lexer_status->lexer_flags.i);
		if (lexer_status->lexer_state == TYPE /* && !isEOF(*format,
			lexer_status->lexer_flags.i)*/)
		{
			if (current_char == 'd' || current_char == 'i')
				process_type(format, lexer_status, &((int){(va_arg(ap, int))}),
					lexer_integer);
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
			{
				printf_putchar(lexer_status, &((char){'%'}));
				consume(format, 0);
			}
		}
	 }

	void process_type(char **format, t_lexer_status *lexer_status, void *arg,
		void (*put_type)(t_lexer_status *, void *))
	{
		(*put_type)(lexer_status, arg);
		consume(format, lexer_status->lexer_flags.i);
	}

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

	void printf_width(t_lexer_status *lexer_status, int effective_width,
		char filler)
	{
		char *str_width;
        if (effective_width <= 0)
            return;
		str_width = malloc(sizeof(char) * (effective_width));
		if (!str_width)
			return ;
		ft_memset(str_width, (int)filler, (effective_width));
		printf_write(lexer_status, str_width, effective_width);
		free(str_width);
	}

	void printf_write(t_lexer_status *lexer_status, char *address, int count)
	{
		int byte_read;

		byte_read = write(1, address, count);
		if (byte_read < count || INT_MAX
			- lexer_status->printed_count < byte_read)
			lexer_status->return_value = -1;
		lexer_status->printed_count += byte_read;
	}

	void lexer_putstr(t_lexer_status *lexer_status, void *arg)
	{
		size_t len;
		void *arg_cpy;

		arg_cpy = arg;
		if (!arg)
			arg = "(null)";
		len = ft_strlen(arg);
		if (lexer_status->lexer_flags.hash || lexer_status->lexer_flags.plus
			|| lexer_status->lexer_flags.zero || lexer_status->lexer_flags.space
			|| len > INT_MAX)
			lexer_status->return_value = -1;
		if (len > INT_MAX)
			return ;
		lexer_putstr2(lexer_status, arg, len, arg_cpy);
	}

	void lexer_putstr2(t_lexer_status *lexer_status, void *arg, size_t len,
		void *arg_cpy)
	{
		if (lexer_status->precision.exist
			&& lexer_status->precision.value < (int)len)
		{
			if (!arg_cpy)
				len = 0;
			else
				len = lexer_status->precision.value;
		}
		if (lexer_status->width)
		{
			if (lexer_status->lexer_flags.minus)
				printf_write(lexer_status, arg, len);
			printf_width(lexer_status, lexer_status->width - len, ' ');
			if (!lexer_status->lexer_flags.minus)
				printf_write(lexer_status, arg, len);
		}
		else
			printf_write(lexer_status, arg, len);
	}

	void lexer_integer(t_lexer_status *lexer_status, void *arg)
{
    size_t int_len;
    char *int_str;
    int sign;

    sign = 1;
    int_len = 0;
    if (lexer_status->lexer_flags.hash)
        lexer_status->return_value = -1;
    if (*((int *)arg) == 0 && ++int_len) 
        int_str = "0";
    else
    {
        if (*((int *)arg) < 0)
            sign = -1;
        printf_utoa_size(sign * (*((int *)arg)), &int_len); 
        int_str = malloc(sizeof(char) * (int_len));
        if (!int_str)
            return;
        printf_utoa(sign * (*((int *)arg)), lexer_status, int_str, int_len);
    }
    lexer_integer2(lexer_status, int_str, int_len, arg);
}

	void lexer_integer2(t_lexer_status *lexer_status, char *int_str,
		size_t int_len, void *arg)
	{
		size_t prefix;

		prefix = integer_get_preffix_size(lexer_status,(*((int *)arg)), int_len);
		if (lexer_status->width)
		{
			if (lexer_status->lexer_flags.minus)
        {
				printf_integer_write(lexer_status, arg, int_str, int_len);
                printf_width(lexer_status, lexer_status->width - int_len - prefix,
				' ');
        }
			if (!lexer_status->lexer_flags.minus)
        {
                printf_integer_prefix(lexer_status, *((int *)arg));
	            printf_width(lexer_status, lexer_status->width - int_len - prefix,
				lexer_status->width_char);
				printf_integer_write(lexer_status, arg, int_str, int_len);
        }
		}
		else
			printf_integer_write(lexer_status, arg, int_str, int_len);
        lexer_integer3(int_str, arg);
	}

void printf_integer_prefix(t_lexer_status * lexer_status,int int_value)
{
    if (int_value > 0)
    {
        if (lexer_status->lexer_flags.plus)
            printf_write(lexer_status, "+", 1);
        else if (lexer_status->lexer_flags.space)
            printf_write(lexer_status, " ", 1);
    }
}

void lexer_integer3(char * int_str, void * arg)
{
    if (*((int *)arg))
        free(int_str);
}


size_t integer_get_preffix_size(t_lexer_status * lexer_status, int int_value, size_t int_len)
{
    size_t prefix;
    prefix = 0;
    
    if (int_value < 0)
        prefix++;
    else if (lexer_status->lexer_flags.plus || lexer_status->lexer_flags.space)
        prefix++;
    if (lexer_status->lexer_flags.zero && !lexer_status->precision.exist)
    {
        lexer_status->width_char = '0';
    }
    else
        lexer_status->width_char = ' ';
    if (lexer_status->precision.exist && (size_t)lexer_status->precision.value > int_len)
        prefix += lexer_status->precision.value - int_len;
    return (prefix);
}

	void lexer_pointer(t_lexer_status *lexer_status, void *arg)
	{
		size_t ptr_len;
		char *ptr_str;

		ptr_len = 0;
		if (lexer_status->lexer_flags.hash || lexer_status->lexer_flags.plus
			|| lexer_status->lexer_flags.zero
			|| lexer_status->lexer_flags.space)
			lexer_status->return_value = -1;
		if (!arg)
		{
			ptr_str = "(nil)";
			ptr_len = 5;
		}
		else
		{
			printf_pointer_size((uintptr_t)arg, &ptr_len);
			ptr_str = malloc(sizeof(char) * ptr_len);// protect all malloc;
            if (!ptr_str)
                return;
			printf_convert_pointer((uintptr_t)arg, lexer_status, ptr_str,
				ptr_len);
		}
		lexer_pointer2(lexer_status, ptr_str, ptr_len, arg);
	}

	void lexer_pointer2(t_lexer_status *lexer_status, char *ptr_str,
		size_t ptr_len, void *arg)
	{
		size_t prefix;

		prefix = 0;
		if (arg)
			prefix = 2;
		if (lexer_status->width)
		{
			if (lexer_status->lexer_flags.minus)
				printf_pointer_write(lexer_status, arg, ptr_str, ptr_len);
			printf_width(lexer_status, lexer_status->width - ptr_len - prefix,
				' ');
			if (!lexer_status->lexer_flags.minus)
				printf_pointer_write(lexer_status, arg, ptr_str, ptr_len);
		}
		else
			printf_pointer_write(lexer_status, arg, ptr_str, ptr_len);
		if (arg)
			free(ptr_str);
	}

	void printf_integer_write(t_lexer_status *lexer_status, void *arg,
		char *int_str, size_t int_len)
	{
        if (*((int *)arg) < 0)
			printf_write(lexer_status, "-", 1);
        else if (lexer_status->width_char == ' ' && lexer_status->lexer_flags.plus)
            printf_write(lexer_status, "+", 1);
        else if (lexer_status->width_char == ' ' && lexer_status->lexer_flags.space)
            printf_write(lexer_status, " ", 1);
        if (lexer_status->precision.exist && (size_t)lexer_status->precision.value > int_len)
            printf_width(lexer_status, lexer_status->precision.value - int_len, '0');
   		printf_write(lexer_status, int_str, int_len);
	}

	void printf_pointer_write(t_lexer_status *lexer_status, void *arg,
		char *ptr_str, size_t ptr_len)
	{
		if (arg)
			printf_write(lexer_status, "0x", 2);
		printf_write(lexer_status, ptr_str, ptr_len);
	}
