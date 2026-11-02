/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quickSort_algorithm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 07:33:19 by jnunez-b          #+#    #+#             */
/*   Updated: 2026/11/02 11:15:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min_index(t_stack *stack, int size)
{
	int	min;

	min = stack->index;
	while (size-- > 0 && stack)
	{
		if (stack->index < min)
			min = stack->index;
		stack = stack->next;
	}
	return (min);
}

static int	get_max_index(t_stack *stack, int size)
{
	int	max;

	max = stack->index;
	while (size-- > 0 && stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

static int	get_pivot(t_stack *stack, int size)
{
	int	min;
	int	max;

	min = get_min_index(stack, size);
	max = get_max_index(stack, size);
	return ((min + max) / 2);
}

void	quick_sort_a(t_stack **a, t_stack **b, int size)
{
	int	pivot;
	int	pushed;
	int	rotated;
	int	i;

	if (size <= 1)
		return ;
	if (size == 2)
	{
		if ((*a)->index > (*a)->next->index)
			sa(a);
		return ;
	}
	if (size == 3)
	{
		sort_three_a(a);
		return ;
	}
	pivot = get_pivot(*a, size);
	pushed = 0;
	rotated = 0;
	i = size;
	while (i--)
	{
		if ((*a)->index <= pivot)
		{
			pb(a, b);
			pushed++;
		}
		else
		{
			ra(a);
			rotated++;
		}
	}
	while (rotated--)
		rra(a);
	quick_sort_a(a, b, size - pushed);
	quick_sort_b(a, b, pushed);
}

void	quick_sort_b(t_stack **a, t_stack **b, int size)
{
	int	pivot;
	int	pushed;
	int	rotated;
	int	i;

	if (size == 0)
		return ;
	if (size == 1)
	{
		pa(a, b);
		return ;
	}
	if (size == 2)
	{
		if ((*b)->index < (*b)->next->index)
			sb(b);
		pa(a, b);
		pa(a, b);
		return ;
	}
	if (size == 3)
	{
		sort_three_b(b);
		pa(a, b);
		pa(a, b);
		pa(a, b);
		return ;
	}
	pivot = get_pivot(*b, size);
	pushed = 0;
	rotated = 0;
	i = size;
	while (i--)
	{
		if ((*b)->index > pivot)
		{
			pa(a, b);
			pushed++;
		}
		else
		{
			rb(b);
			rotated++;
		}
	}
	while (rotated--)
		rrb(b);
	quick_sort_a(a, b, pushed);
	quick_sort_b(a, b, size - pushed);
}

void	quick_sort(t_stack **stack_a, t_stack **stack_b)
{
	index_list(*stack_a);
	quick_sort_a(stack_a, stack_b, stack_size(*stack_a));
}
