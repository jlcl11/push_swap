/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 12:32:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/08 10:00:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"

int	ft_printf(char const *format, ...);
int	ft_parser(char c, va_list *args);
int	ft_format(char const **format_addr, va_list *args);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr_base(long nbr, char *base);
int	ft_putnbr_ubase(unsigned long nbr, char *base);
int	puntero(void *ptr);

#endif
