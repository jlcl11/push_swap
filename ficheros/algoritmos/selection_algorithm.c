/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_algorithm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:53:42 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 13:39:34 by jnunez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** is_sorted: devuelve 1 si la pila está ordenada de menor a mayor.
*/

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

/* Devuelve la posición del mínimo, contando desde la cima (0) */

static int	get_min_pos(t_stack *stack)
{
	int	min;
	int	pos;
	int	i;

	min = stack->value;
	pos = 0;
	i = 0;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			pos = i;
		}
		stack = stack->next;
		i++;
	}
	return (pos);
}

/* Sube el mínimo a la cima por el camino más corto: ra o rra */

static void	min_to_top(t_stack **a, t_flags *flags)
{
	int	pos;
	int	size;

	pos = get_min_pos(*a);
	size = stack_size(*a);
	if (pos <= size / 2)
		while (pos-- > 0)
			ra(a, flags);
	else
		while (pos++ < size)
			rra(a, flags);
}

/*
** algoritmo_simple: selección, O(n²).
** Sube el mínimo de a a la cima y lo pasa a b, de modo que b guarda los
** mínimos con el mayor arriba. Cuando lo que queda en a ya está ordenado,
** se devuelve todo con pa y los mínimos quedan encima en su orden.
*/

void	selection_sort(t_stack **a, t_stack **b, t_flags *flags)
{
	if (!a || !*a)
		return ;
	while (!is_sorted(*a))
	{
		min_to_top(a, flags);
		if (!is_sorted(*a))
			pb(a, b, flags);
	}
	while (*b)
		pa(a, b, flags);
	flags->complexity = "O(n²)";
}
