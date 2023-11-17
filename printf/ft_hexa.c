/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:08:59 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/24 13:34:13 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa(unsigned long long n, char c)
{
	unsigned long long	count;

	count = 0;
	if (n >= 16)
		count += ft_hexa(n / 16, c);
	if (c == 'x')
		ft_putchar("0123456789abcdef" [n % 16]);
	else if (c == 'X')
		ft_putchar("0123456789ABCDEF" [n % 16]);
	count++;
	return (count);
}
