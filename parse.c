/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parse.c                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/23 16:00:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/23 17:28:08 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Devuelve 1 si algún valor aparece más de una vez en la pila, 0 si no.
** Compara ya convertidos a int, así "0", "-0" y "00" cuentan como repes.
*/

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
