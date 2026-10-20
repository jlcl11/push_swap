/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   algorithm.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/19 15:53:42 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/19 18:02:22 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Petalo, cactus y

/*
** is_sorted: devuelve 1 si la pila está ordenada de menor a mayor.
*/

static int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

/*
** algoritmo_simple: burbuja usando solo sa y ra.
** En cada pasada se recorre la pila entera: si la cima es mayor que el
** segundo se hace sa, y luego ra para avanzar. Así el mayor "flota"
** hacia el fondo. Tras size rotaciones la pila vuelve a su posición.
** Se repite hasta que esté ordenada.
*/

void	bubble_sort(t_stack **stack)
{
	int	size;
	int	i;

	if (!stack || !*stack)
		return ;
	size = stack_size(*stack);
	while (!is_sorted(*stack))
	{
		i = 0;
		while (i < size - 1)
		{
			if ((*stack)->value > (*stack)->next->value)
			{
				sa(stack);
			}
			ra(stack);
			i++;
		}
		ra(stack);
	}
}
