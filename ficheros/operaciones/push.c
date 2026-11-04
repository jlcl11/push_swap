/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   push.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/16 16:00:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/11/04 11:35:48 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_stack **src, t_stack **dst)
{
	t_stack	*node;

	if (!src || !*src || !dst)
		return ;
	node = *src;
	*src = node->next;
	stack_push(dst, node);
}

void	pa(t_stack **a, t_stack **b, t_flags *flags)
{
	push(b, a);
	record_op(flags, &flags->pa, "pa");
}

void	pb(t_stack **a, t_stack **b, t_flags *flags)
{
	push(a, b);
	record_op(flags, &flags->pb, "pb");
}
