/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:13:59 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/25 11:04:41 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 0 && nb <= 9)
		ft_putchar(nb + '0');
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

static int	ft_counter(long int n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

int	ft_decient(int nb)
{
	long int	a;

	a = 0;
	ft_putnbr(nb);
	if (nb >= 0)
		return (ft_counter(nb));
	a = (long int)nb * (-1);
	return (ft_counter(a) + 1);
}
