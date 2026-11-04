/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:10:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 12:49:59 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	rra(t_stack **a, t_flags *flags)
{
	reverse_rotate(a);
	record_op(flags, &flags->rra, "rra");
}

void	rrb(t_stack **b, t_flags *flags)
{
	reverse_rotate(b);
	record_op(flags, &flags->rrb, "rrb");
}

void	rrr(t_stack **a, t_stack **b, t_flags *flags)
{
	reverse_rotate(a);
	reverse_rotate(b);
	record_op(flags, &flags->rrr, "rrr");
}
