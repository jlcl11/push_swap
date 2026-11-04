/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 07:12:57 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/02 11:15:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(t_stack *stack)
{
	t_stack	*i;
	t_stack	*j;
	int		pairs;
	int		mistakes;

	pairs = 0;
	mistakes = 0;
	i = stack;
	while (i)
	{
		j = i->next;
		while (j)
		{
			pairs++;
			if (i->value > j->value)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	if (mistakes == 0)
		return (0.0);
	return ((double)mistakes / pairs);
}
