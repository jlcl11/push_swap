/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 11:30:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/12 11:30:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_putpad(char c, int n)
{
	int	count;

	count = 0;
	while (count < n)
	{
		ft_putchar(c);
		count++;
	}
	return (count);
}

static int	nbr_len(unsigned long n, unsigned long base_len)
{
	int	len;

	len = 1;
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

static int	zero_count(t_format *f, int digits, int prefix_len)
{
	if (f->prec >= 0)
	{
		if (f->prec > digits)
			return (f->prec - digits);
		return (0);
	}
	if (f->zero && !f->minus && f->width > digits + prefix_len)
		return (f->width - digits - prefix_len);
	return (0);
}

int	ft_put_nbr(t_format *f, unsigned long n, char *prefix)
{
	int	digits;
	int	zeros;
	int	prefix_len;
	int	count;

	prefix_len = ft_strlen(prefix);
	digits = nbr_len(n, ft_strlen(f->base));
	if (n == 0 && f->prec == 0)
		digits = 0;
	zeros = zero_count(f, digits, prefix_len);
	count = 0;
	if (!f->minus)
		count += ft_putpad(' ', f->width - prefix_len - zeros - digits);
	count += ft_putstr(prefix);
	count += ft_putpad('0', zeros);
	if (digits)
		count += ft_putnbr_ubase(n, f->base);
	if (f->minus)
		count += ft_putpad(' ', f->width - count);
	return (count);
}
