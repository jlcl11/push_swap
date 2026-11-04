/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_algorithm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:53:42 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 14:03:46 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static int	get_min_pos(t_stack *stack)
{
	int	min;
	int	pos;
	int	i;

	min = stack->value;
	pos = 0;
	i = 0;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			pos = i;
		}
		stack = stack->next;
		i++;
	}
	return (pos);
}

static void	min_to_top(t_stack **a, t_flags *flags)
{
	int	pos;
	int	size;

	pos = get_min_pos(*a);
	size = stack_size(*a);
	if (pos <= size / 2)
		while (pos-- > 0)
			ra(a, flags);
	else
		while (pos++ < size)
			rra(a, flags);
}

void	selection_sort(t_stack **a, t_stack **b, t_flags *flags)
{
	flags->disorder = compute_disorder(*a);
	if (!a || !*a)
		return ;
	while (!is_sorted(*a))
	{
		min_to_top(a, flags);
		if (!is_sorted(*a))
			pb(a, b, flags);
	}
	while (*b)
		pa(a, b, flags);
	flags->complexity = "O(n²)";
}
