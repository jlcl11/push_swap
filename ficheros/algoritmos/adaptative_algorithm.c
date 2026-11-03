/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptative_algorithm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 13:49:16 by jnunez-b          #+#    #+#             */
/*   Updated: 2026/11/03 18:10:32 by jnunez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack **stack, t_flags *flags)
{
	int	first;
	int	second;
	int	third;

	flags->complexity = "O(1)";
	first = (*stack)->index;
	second = (*stack)->next->index;
	third = (*stack)->next->next->index;
	if (first > second && second < third && first < third)
		sa(stack, flags);
	else if (first > second && second > third)
	{
		sa(stack, flags);
		rra(stack, flags);
	}
	else if (first > second && second < third && first > third)
		ra(stack, flags);
	else if (first < second && second > third && first < third)
	{
		sa(stack, flags);
		ra(stack, flags);
	}
	else if (first < second && second > third && first > third)
		rra(stack, flags);
}

void	adaptative_sort(t_stack **stack_a, t_stack **stack_b, t_chunk *chunky,
	t_flags *flags)
{
	int		size;

	flags->disorder = compute_disorder(*stack_a);
	size = stack_size(*stack_a);
	index_list(*stack_a);
	if (size < 2 || !flags->disorder)
		return ;
	if (size == 2)
		sa(stack_a, flags);
	else if (size == 3)
		sort_three(stack_a, flags);
	else if (size <= 5 || flags->disorder < 0.2)
		selection_sort(stack_a, stack_b, flags);
	else if (flags->disorder >= 0.2 && flags->disorder < 0.5)
	{
		chunk_sort(stack_a, stack_b, chunky, flags);
		flags->complexity = "O(n√n)";
	}
	else if (flags->disorder >= 0.5)
	{
		radix_sort(stack_a, stack_b, flags);
		flags->complexity = "O(nlogn)";
	}
}
