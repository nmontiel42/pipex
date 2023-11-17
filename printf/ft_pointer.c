/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:44:49 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/24 13:41:47 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pointer(unsigned long long ptr)
{
	int	c;

	c = 0;
	c += ft_string("0x");
	c += ft_hexa(ptr, 'x');
	return (c);
}
