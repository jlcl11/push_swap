/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:02:54 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 12:51:30 by jnunez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	ra(t_stack **a, t_flags *flags)
{
	rotate(a);
	record_op(flags, &flags->ra, "ra");
}

void	rb(t_stack **b, t_flags *flags)
{
	rotate(b);
	record_op(flags, &flags->rb, "rb");
}

void	rr(t_stack **a, t_stack **b, t_flags *flags)
{
	rotate(a);
	rotate(b);
	record_op(flags, &flags->rr, "rr");
}
