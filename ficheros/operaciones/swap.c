/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   swap.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/16 12:10:08 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/16 13:51:48 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** swap: intercambia los dos primeros elementos de la cima de la pila.
** No hace nada si hay uno o ningún elemento. No imprime nada.
**
**   antes:   [1] -> [2] -> [3]
**   después: [2] -> [1] -> [3]
*/

static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

/* sa (swap a): swap sobre a */

void	sa(t_stack **a)
{
	swap(a);
	ft_printf("sa\n");
}

/* sb (swap b): swap sobre b */

void	sb(t_stack **b)
{
	swap(b);
	ft_printf("sb\n");
}

/* ss: sa y sb a la vez, imprime una sola línea */

void	ss(t_stack **a, t_stack **b)
{
	swap(a);
	swap(b);
	ft_printf("ss\n");
}
