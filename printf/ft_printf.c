/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:08:43 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/24 13:47:23 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

static int	ft_filter(char const *content, int i, va_list *args)
{
	int	a;

	a = 0;
	if (content[i] == 'c')
		a += ft_putchar(va_arg(*args, int));
	if (content[i] == 's')
		a += ft_string(va_arg(*args, char *));
	if (content[i] == 'p')
		a += ft_pointer(va_arg(*args, unsigned long long));
	if (content[i] == 'd')
		a += ft_decient(va_arg(*args, int));
	if (content[i] == 'i')
		a += ft_decient(va_arg(*args, int));
	if (content[i] == 'u')
		a += ft_unsigned(va_arg(*args, unsigned int));
	if (content[i] == 'x')
		a += ft_hexa(va_arg(*args, unsigned int), 'x');
	if (content[i] == 'X')
		a += ft_hexa(va_arg(*args, unsigned int), 'X');
	if (content[i] == '%')
		a += ft_putchar('%');
	return (a);
}

int	ft_printf(char const *content, ...)
{
	va_list	args;
	int		i;
	int		c;

	i = 0;
	c = 0;
	va_start(args, content);
	while (content[i])
	{
		if (content[i] != '%')
			c += ft_putchar(content[i]);
		else
		{
			i++;
			c += ft_filter(content, i, &args);
		}
		i++;
	}
	va_end(args);
	return (c);
}
