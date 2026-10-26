/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 11:30:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/12 11:30:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_print_char(t_format *f, int c)
{
	int	count;

	count = 0;
	if (!f->minus)
		count += ft_putpad(' ', f->width - 1);
	count += ft_putchar(c);
	if (f->minus)
		count += ft_putpad(' ', f->width - 1);
	return (count);
}

int	ft_print_str(t_format *f, char *s)
{
	int	len;
	int	i;

	if (!s && f->prec >= 0 && f->prec < 6)
		s = "";
	else if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (f->prec >= 0 && f->prec < len)
		len = f->prec;
	if (!f->minus)
		ft_putpad(' ', f->width - len);
	i = 0;
	while (i < len)
		ft_putchar(s[i++]);
	if (f->minus)
		ft_putpad(' ', f->width - len);
	if (f->width > len)
		return (f->width);
	return (len);
}

int	ft_print_int(t_format *f, long n)
{
	f->base = "0123456789";
	if (n < 0)
		return (ft_put_nbr(f, -n, "-"));
	if (f->plus)
		return (ft_put_nbr(f, n, "+"));
	if (f->space)
		return (ft_put_nbr(f, n, " "));
	return (ft_put_nbr(f, n, ""));
}

int	ft_print_uint(t_format *f, unsigned long n, char spec)
{
	f->base = "0123456789";
	if (spec == 'x')
		f->base = "0123456789abcdef";
	else if (spec == 'X')
		f->base = "0123456789ABCDEF";
	if (f->hash && n != 0 && spec == 'x')
		return (ft_put_nbr(f, n, "0x"));
	if (f->hash && n != 0 && spec == 'X')
		return (ft_put_nbr(f, n, "0X"));
	return (ft_put_nbr(f, n, ""));
}

int	ft_print_ptr(t_format *f, void *ptr)
{
	if (!ptr)
	{
		f->prec = -1;
		return (ft_print_str(f, "(nil)"));
	}
	f->base = "0123456789abcdef";
	if (f->plus)
		return (ft_put_nbr(f, (unsigned long)ptr, "+0x"));
	if (f->space)
		return (ft_put_nbr(f, (unsigned long)ptr, " 0x"));
	return (ft_put_nbr(f, (unsigned long)ptr, "0x"));
}
