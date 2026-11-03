/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 12:32:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 17:44:42 by jnunez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_ERROR_H
#define FT_PRINTF_ERROR_H

# include <stdarg.h>
# include "../libft/libft.h"

int	ft_printf_error(char const *format, ...);
int	ft_parser(char c, va_list *args);
int	ft_format(char const **format_addr, va_list *args);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr_base(long nbr, char *base);
int	ft_putnbr_ubase(unsigned long nbr, char *base);
int	puntero(void *ptr);

#endif
