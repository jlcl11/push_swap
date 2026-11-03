/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_algorithm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 13:49:16 by jnunez-b          #+#    #+#             */
/*   Updated: 2026/11/03 14:03:27 by jnunez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(int size)
{
	int	max;
	int	bits;

	max = size - 1;
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	radix_sort(t_stack **stack_a, t_stack **stack_b, t_flags *flags)
{
	int	max_bits;
	int	size;
	int	i;
	int	j;

	flags->disorder = compute_disorder(*stack_a);
	size = stack_size(*stack_a);
	max_bits = get_max_bits(size);
	index_list(*stack_a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if ((((*stack_a)->index >> i) & 1) == 0)
				pb(stack_a, stack_b, flags);
			else
				ra(stack_a, flags);
			j++;
		}
		while (*stack_b)
			pa(stack_a, stack_b, flags);
		i++;
	}
}
