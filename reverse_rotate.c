/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   reverse_rotate.c                                  :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/16 14:10:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/16 14:10:00 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** reverse_rotate: el último elemento pasa a ser el primero. No imprime nada.
** Suelta el último nodo y lo mete en la cima con stack_push.
**
**   antes:   [1] -> [2] -> [3]
**   después: [3] -> [1] -> [2]
*/

static void	reverse_rotate(t_stack **stack)
{
	t_stack	*before_last;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	before_last = *stack;
	while (before_last->next->next)
		before_last = before_last->next;
	last = before_last->next;
	before_last->next = NULL;
	stack_push(stack, last);
}

/* rra (reverse rotate a): reverse_rotate sobre a */

void	rra(t_stack **a)
{
	reverse_rotate(a);
	ft_printf("rra\n");
}

/* rrb (reverse rotate b): reverse_rotate sobre b */

void	rrb(t_stack **b)
{
	reverse_rotate(b);
	ft_printf("rrb\n");
}

/* rrr: rra y rrb a la vez, imprime una sola línea */

void	rrr(t_stack **a, t_stack **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ft_printf("rrr\n");
}
