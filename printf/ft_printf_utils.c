/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/08 10:00:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	if (!str)
		str = "(null)";
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_putnbr_ubase(unsigned long nbr, char *base)
{
	unsigned long	len;
	int				count;

	len = ft_strlen(base);
	count = 0;
	if (nbr >= len)
		count += ft_putnbr_ubase(nbr / len, base);
	count += ft_putchar(base[nbr % len]);
	return (count);
}

int	ft_putnbr_base(long nbr, char *base)
{
	if (nbr < 0)
		return (ft_putchar('-') + ft_putnbr_ubase(-nbr, base));
	return (ft_putnbr_ubase(nbr, base));
}

int	puntero(void *ptr)
{
	if (!ptr)
		return (ft_putstr("(nil)"));
	return (ft_putstr("0x")
		+ ft_putnbr_ubase((unsigned long)ptr, "0123456789abcdef"));
}
