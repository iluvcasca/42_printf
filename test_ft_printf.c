/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:44:23 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/20 18:28:58 by kgriset          ###   ########.fr       */
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
    long    k;
    long    l;
    long    m;
    long    n;
    long    o;
    long    p;
    long    q;
    long    r;
    long    s;


	clock_t start, end;
	start = clock();
	// -- %c
	// 1
	// long a = ft_printf("%2147483646c\n", 'b');
	// printf("%li\n",a);
	// fflush(stdout);
	// 2
	// long b = ft_printf("%2147483647c\n", 'b');
	// printf("%li\n",b);
	// fflush(stdout);
	// 3
	c = ft_printf("%-42c\n", 'b');
	printf("%li\n", c);
	fflush(stdout);
	// 4
	d = ft_printf("%c\n", 'b');
	printf("%li\n", d);
	fflush(stdout);
	// -- %s
	// 5
	e = ft_printf("%.2s\n", (char *)NULL);
	printf("%li\n", e);
	fflush(stdout);
	// 6
	f = ft_printf("..%-43.2s..\n", (char *)NULL);
	printf("%li\n", f);
	fflush(stdout);
	// 7
	g = ft_printf("..%-43.3s..\n", "hello");
	printf("%li\n", g);
	fflush(stdout);
    // 7.1
	ga = ft_printf("..%-3.3s..\n", "hello");
	printf("%li\n", ga);
	fflush(stdout);
	// -- %p
	// 8
	h = ft_printf("..%-13p..\n", NULL);
	printf("%li\n", h);
	fflush(stdout);
	// 9
	ptr = malloc(sizeof(char));
	i = ft_printf("..%-20p..\n", ptr);
	printf("%li\n", i);
	fflush(stdout);
	free(ptr);
	// 10
	j = ft_printf("..%2p..\n", NULL);
	printf("%li\n", j);
	fflush(stdout);
    // -- %i/d
    // 11
    k = ft_printf("..%i..\n", 0);
	printf("%li\n", k);
	fflush(stdout);
    // 12
    l = ft_printf("..%042i..\n", 0);
	printf("%li\n", l);
	fflush(stdout);
    // 13
    m = ft_printf("..%-042i..\n", 0);
	printf("%li\n", m);
	fflush(stdout);
    // 14
    n = ft_printf("..% 042i..\n", 6);
	printf("%li\n", n);
	fflush(stdout);
    // 15
    o = ft_printf("..%+042i..\n", 7);//
	printf("%li\n", o);
	fflush(stdout);
    // 16
    p = ft_printf("..%-42.5i..\n", -7);//
	printf("%li\n", p);
	fflush(stdout);
    // 17
    q = ft_printf("..%+042.1i..\n", 7);//
	printf("%li\n", q);
	fflush(stdout);
    // 18
    r = ft_printf("..%+042.0i..\n", -7);//
	printf("%li\n", r);
	fflush(stdout);
    // 19
    s = ft_printf("..%+042.i..\n", 7);//
	printf("%li\n", s);
	fflush(stdout);


	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Took : %f seconds\n", cpu_time_used);
	return (1);
}
