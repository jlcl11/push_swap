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

void	sa(t_stack **a, t_flags *flags)
{
	swap(a);
	flags->sa++;
	flags->total++;
	ft_printf("sa\n");
}

void	sb(t_stack **b, t_flags *flags)
{
	swap(b);
	flags->sb++;
	flags->total++;
	ft_printf("sb\n");
}

void	ss(t_stack **a, t_stack **b, t_flags *flags)
{
	swap(a);
	swap(b);
	flags->ss++;
	flags->total++;
	ft_printf("ss\n");
}
