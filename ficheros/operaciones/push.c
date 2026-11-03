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

/*
** push: saca el primer elemento de src y lo pone en la cima de dst.
** No hace nada si src está vacía. No imprime nada.
**
**   antes:   src: [1] -> [2]    dst: [3]
**   después: src: [2]           dst: [1] -> [3]
*/

static void	push(t_stack **src, t_stack **dst)
{
	t_stack	*node;

	if (!src || !*src || !dst)
		return ;
	node = *src;
	*src = node->next;
	stack_push(dst, node);
}

/* pa (push a): toma el primer elemento de b y lo pone encima de a */

void	pa(t_stack **a, t_stack **b, t_flags *flags)
{
	push(b, a);
	flags->pa++;
	flags->total++;
	ft_printf("pa\n");
}

/* pb (push b): toma el primer elemento de a y lo pone encima de b */

void	pb(t_stack **a, t_stack **b, t_flags *flags)
{
	push(a, b);
	flags->pb++;
	flags->total++;
	ft_printf("pb\n");
}
