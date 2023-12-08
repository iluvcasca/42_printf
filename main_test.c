/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:24:10 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/08 15:47:58 by kgriset          ###   ########.fr       */
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
    char * test = "";
    int a = sizeof(char *);
    int b = sizeof(int *);
    int c = sizeof (long);
    unsigned long e = (unsigned long)(test);
    printf("%p\n" , test);
    printf("0x%lx\n" , e);
    long d = printf("%p", (char *)NULL);
    printf("\n%ld", d);
    return (1);
}
