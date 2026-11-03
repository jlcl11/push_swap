/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 12:26:09 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/19 12:59:36 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parser(char c, va_list *args)
{
	if (c == '\0')
		return (0);
	else if (c == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (c == 'p')
		return (puntero(va_arg(*args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_base(va_arg(*args, int), "0123456789"));
	else if (c == 'u')
		return (ft_putnbr_ubase(va_arg(*args, unsigned int), "0123456789"));
	else if (c == 'x')
		return (ft_putnbr_ubase(va_arg(*args, unsigned int),
				"0123456789abcdef"));
	else if (c == 'X')
		return (ft_putnbr_ubase(va_arg(*args, unsigned int),
				"0123456789ABCDEF"));
	else if (c == '%')
		return (ft_putchar('%'));
	return (ft_putchar('%') + ft_putchar(c));
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format != '%')
			count += ft_putchar(*format);
		else
		{
			format++;
			count += ft_format(&format, &args);
			if (!*format)
				break ;
		}
		format++;
	}
	va_end(args);
	return (count);
}
