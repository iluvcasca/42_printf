/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:44:23 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/16 18:15:19 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <time.h>
int main ()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // 1
    // long a = printf("%2147483646c\n", 'b');
    // printf("%li\n",h);

    long b = printf("%2147483647c\n", 'b');
    printf("%li\n",b);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Took : %f seconds\n", cpu_time_used);
    return (1);
}
