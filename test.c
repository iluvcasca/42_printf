/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:44:23 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/15 17:31:10 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
int main ()
{
    // char * str = "want to build %% my %# 00--9999999999i keyboard %i\n";
    // char * str = "want to build my %# 00--2147483648.2147483648i keyboard %i\n";
    // char * str = "want to build my %47483648.2147483647%i keyboard %00--##  \n";
    // unsigned int int2 = (unsigned int)-1;
    // unsigned int int1 = 0;
    int int1 = INT_MIN;
    int int2 = INT_MAX;
    // char * str1 = "awesome";
    // char * str2 = NULL;
    // char * current_char = str;
    // char p;
    // char c;
    // int i = 0; 
    // while (str[i])
    // {
    //     p = peek(&str, 0);
    //     p = peek(&str, 0);
    //     c = consume(&str, 1);
    //     i++;
    // }
    // ft_printf((const char *)str, str1, str2);
    // printf("\n");
    // printf((const char *)str ,str1, str2);
    // long a = ft_printf((const char *)str, int1, int2);
    // long a = ft_printf((const char *)str);
    // long b = printf((const char *)str);
    // long x = ft_printf(" ");
    // printf("\n");
    // long b = printf((const char *)str ,int1, int2);
    // printf("\n%li", a);
    // printf("\n%li", x);
    // printf("\n%li\n", b);
    // long g = printf("%2147483647c",'a');
    // printf("\n");
    long h = ft_printf("%2147483647c", 'b');
    printf("\n");
    // printf("%li\n",g);
    printf("%li\n",h);
    

    return (1);
}
