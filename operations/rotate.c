/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   rotate.c                                          :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/16 14:02:54 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/16 14:03:12 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** rotate: el primer elemento pasa a ser el último. No imprime nada.
** Saca la cima y la mete al fondo con stack_add_back.
**
**   antes:   [1] -> [2] -> [3]
**   después: [2] -> [3] -> [1]
*/

static void	rotate(t_stack **stack)
{
	t_stack	*first;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	*stack = first->next;
	first->next = NULL;
	stack_add_back(stack, first);
}

/* ra (rotate a): rotate sobre a */

void	ra(t_stack **a)
{
	rotate(a);
	ft_printf("ra\n");
}

/* rb (rotate b): rotate sobre b */

void	rb(t_stack **b)
{
	rotate(b);
	ft_printf("rb\n");
}

/* rr: ra y rb a la vez, imprime una sola línea */

void	rr(t_stack **a, t_stack **b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
}
