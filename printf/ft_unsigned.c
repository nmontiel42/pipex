/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:01:40 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/24 13:47:06 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned(unsigned int uns)
{
	int	c;

	c = 0;
	if (uns >= 10)
		c += ft_unsigned(uns / 10);
	ft_putchar(uns % 10 + '0');
	c++;
	return (c);
}
