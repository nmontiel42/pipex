/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:45:41 by nmontiel          #+#    #+#             */
/*   Updated: 2023/05/24 13:47:18 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>

int	ft_printf(char const *content, ...);
int	ft_decient(int nb);
int	ft_hexa(unsigned long long n, char c);
int	ft_pointer(unsigned long long ptr);
int	ft_string(char *str);
int	ft_unsigned(unsigned int uns);
int	ft_putchar(char c);

#endif