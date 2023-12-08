/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:44:23 by kgriset           #+#    #+#             */
/*   Updated: 2023/12/08 19:04:21 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
int main ()
{
    char * str = "want to build %% my %p keyboard %p";
    char * str1 = "awesome";
    char * str2 = NULL;
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
    ft_printf((const char *)str, str1, str2);
    printf("\n");
    printf((const char *)str ,str1, str2);
    return (1);
}
