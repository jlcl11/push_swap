/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunck_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 07:12:57 by jnunez-b          #+#    #+#             */
/*   Updated: 2026/11/02 11:15:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	index_list(t_stack *stack)
{
	int		index;
	t_stack	*i;
	t_stack	*j;

	i = stack;
	while (i)
	{
		index = 0;
		j = stack;
		while (j)
		{
			if (i->value > j->value)
				index++;
			j = j->next;
		}
		i->index = index;
		i = i->next;
	}
}

static void	move_to_top(t_stack **stack, int target, int is_b)
{
	int		size;
	int		poss;
	t_stack	*i;

	i = *stack;
	poss = 0;
	size = stack_size(*stack);
	while (i->index != target)
	{
		poss++;
		i = i->next;
	}
	while ((*stack)->index != target)
	{
		if (poss <= size / 2 && is_b)
			rb(stack);
		else if (poss <= size / 2)
			ra(stack);
		else if (is_b)
			rrb(stack);
		else
			rra(stack);
	}
}

static void	push_chunk(t_stack **stack_a, t_stack **stack_b, int start, int end)
{
	int		j;
	t_stack	*i;

	while (1)
	{
		i = *stack_a;
		while (i && (i->index < start || i->index >= end))
			i = i->next;
		if (!i)
			break ;
		j = i->index;
		move_to_top(stack_a, j, 0);
		pb(stack_a, stack_b);
		if (j < start + (end - start) / 2)
			rb(stack_b);
	}
}

static int	round_sqrt(int size)
{
	int	i;

	i = 0;
	while ((i + 1) * (i + 1) <= size)
		i++;
	if ((size - (i * i)) >= ((i + 1) * (i + 1) - size))
		i++;
	return (i);
}

void	chunk_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	chunk;
	int	start;
	int	end;
	int	size;
	int	max_index;

	index_list(*stack_a);
	size = stack_size(*stack_a);
	chunk = round_sqrt(size);
	start = 0;
	while (start < size)
	{
		end = start + chunk;
		if (end > size)
			end = size;
		push_chunk(stack_a, stack_b, start, end);
		start = end;
	}
	max_index = size - 1;
	while (*stack_b)
	{
		move_to_top(stack_b, max_index, 1);
		pa(stack_a, stack_b);
		max_index--;
	}
}
