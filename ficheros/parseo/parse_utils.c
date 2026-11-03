/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parse_utils.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/26 12:00:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/26 12:00:00 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] && ft_strchr("+-", str[i]))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	sign;
	long	n;

	sign = 1;
	n = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		if (n > (long)INT_MAX + 1)
			break ;
		str++;
	}
	return (sign * n);
}

int	has_duplicates(t_stack *stack)
{
	t_stack	*other;

	while (stack)
	{
		other = stack->next;
		while (other)
		{
			if (stack->value == other->value)
				return (1);
			other = other->next;
		}
		stack = stack->next;
	}
	return (0);
}
