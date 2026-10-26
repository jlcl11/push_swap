/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 11:30:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/12 11:30:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include "ft_printf.h"

typedef struct s_format
{
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		prec;
	char	*base;
}	t_format;

int	ft_putpad(char c, int n);
int	ft_put_nbr(t_format *f, unsigned long n, char *prefix);
int	ft_print_char(t_format *f, int c);
int	ft_print_str(t_format *f, char *s);
int	ft_print_int(t_format *f, long n);
int	ft_print_uint(t_format *f, unsigned long n, char spec);
int	ft_print_ptr(t_format *f, void *ptr);

#endif
