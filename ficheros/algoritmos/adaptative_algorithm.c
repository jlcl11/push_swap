/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptative_algorithm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 13:49:16 by jnunez-b          #+#    #+#             */
/*   Updated: 2026/11/03 12:03:39 by jnunez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack **stack)
{
	int	first;
	int	second;
	int	third;

	first = (*stack)->index;
	second = (*stack)->next->index;
	third = (*stack)->next->next->index;
	if (first > second && second < third && first < third)
		sa(stack);
	else if (first > second && second > third)
	{
		sa(stack);
		rra(stack);
	}
	else if (first > second && second < third && first > third)
		ra(stack);
	else if (first < second && second > third && first < third)
	{
		sa(stack);
		ra(stack);
	}
	else if (first < second && second > third && first > third)
		rra(stack);
}

static int	find_min_index(t_stack *stack)
{
	int		min;
	t_stack	*i;

	i = stack;
	min = i->index;
	while (i)
	{
		if (i->index < min)
			min = i->index;
		i = i->next;
	}
	return (min);
}

void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	int	min_index;
	int	size;

	while(stack_size(*stack_a))
	{
		min_index = find_min_index(*stack_a);
		size = stack_size(*stack_a);
		if (min_index <= size /2)
		{
			while ((*stack_a)->index != min_index)
				ra(stack_a);
		}
		else
		{
			while ((*stack_a)->index != min_index)
				rra(*stack_a);
		}
		pb(stack_a, stack_b);
		sort_three(stack_a);
		while (*stack_b)
			pa(stack_a, stack_b);
	}
}

void	adaptative_sort(t_stack **stack_a, t_stack **stack_b)
{
	double	disorder;
	int		size;

	disorder = compute_disorder(*stack_a);
	size = stack_size(*stack_a);
	index_list(*stack_a);
	if (size < 2 || !disorder)
		return ;
	if (size == 2)
		sa(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size <= 5)
		sort_five(stack_a, stack_b);
	else if (disorder < 0.2)
		selection_sort(stack_a, stack_b);
	else if (disorder >= 0.2 && disorder < 0.5)
		chunk_sort(stack_a, stack_b);
	else if (disorder >= 0.5)
		radix_sort(stack_a, stack_b);
}
