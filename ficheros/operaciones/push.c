/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 16:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 12:47:55 by jnunez-b         ###   ########.fr       */
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
	flags->pa++;
	flags->total++;
	ft_printf("pa\n");
}

void	pb(t_stack **a, t_stack **b, t_flags *flags)
{
	push(a, b);
	flags->pb++;
	flags->total++;
	ft_printf("pb\n");
}
