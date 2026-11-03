/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 12:10:08 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 12:54:30 by jnunez-b         ###   ########.fr       */
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

void	sa(t_stack **a, t_flags *flags)
{
	swap(a);
	flags->sa++;
	flags->total++;
	ft_printf("sa\n");
}

/* sb (swap b): swap sobre b */

void	sb(t_stack **b, t_flags *flags)
{
	swap(b);
	flags->sb++;
	flags->total++;
	ft_printf("sb\n");
}

/* ss: sa y sb a la vez, imprime una sola línea */

void	ss(t_stack **a, t_stack **b, t_flags *flags)
{
	swap(a);
	swap(b);
	flags->ss++;
	flags->total++;
	ft_printf("ss\n");
}
