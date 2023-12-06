/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:24:10 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/06 14:36:52 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

int main()
{
    // void * p;
    // printf("%%p void * : %p\n", p);
    // printf("%%s        : %s\n", "ousmane");
    // printf("%%u        : %u\n", (unsigned int)-1);
    // printf("%%x        : %#3.x\n", (unsigned int)-1);
    // printf("%%f        : %#f\n", -1.01264567);
    // printf("%%f        : %#.3f\n", -1.01264567);
    long d = printf("hellllllllll %2147483647d hehfiehfhfhei", 10);
    printf("\n%ld", d);
    return (1);
}
