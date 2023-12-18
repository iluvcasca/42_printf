/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:44:23 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/18 15:20:00 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <time.h>

int	main(void)
{
	double	cpu_time_used;
	long	c;
	long	d;
	long	e;
	long	f;
	long	g;
    long    ga;
	long	h;
	char	*ptr;
	long	i;
	long	j;

	clock_t start, end;
	start = clock();
	// -- %c
	// 1
	// long a = printf("%2147483646c\n", 'b');
	// printf("%li\n",a);
	// fflush(stdout);
	// 2
	// long b = printf("%2147483647c\n", 'b');
	// printf("%li\n",b);
	// fflush(stdout);
	// 3
	c = printf("%-42c\n", 'b');
	printf("%li\n", c);
	fflush(stdout);
	// 4
	d = printf("%c\n", 'b');
	printf("%li\n", d);
	fflush(stdout);
	// -- %s
	// 5
	e = printf("%.2s\n", (char *)NULL);
	printf("%li\n", e);
	fflush(stdout);
	// 6
	f = printf("..%-43.2s..\n", (char *)NULL);
	printf("%li\n", f);
	fflush(stdout);
	// 7
	g = printf("..%-43.3s..\n", "hello");
	printf("%li\n", g);
	fflush(stdout);
    // 7.1
	ga = printf("..%-3.3s..\n", "hello");
	printf("%li\n", ga);
	fflush(stdout);
	// -- %p
	// 8
	h = printf("..%-13p..\n", NULL);
	printf("%li\n", h);
	fflush(stdout);
	// 9
	ptr = malloc(sizeof(char));
	i = printf("..%-20p..\n", ptr);
	printf("%li\n", i);
	fflush(stdout);
	free(ptr);
	// 10
	j = printf("..%2p..\n", NULL);
	printf("%li\n", j);
	fflush(stdout);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Took : %f seconds\n", cpu_time_used);
	return (1);
}
