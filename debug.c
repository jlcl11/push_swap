/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   debug.c                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/16 12:00:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/23 17:36:43 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Solo para depurar: no se llama en la entrega, porque la salida del
** programa tiene que ser únicamente la lista de operaciones.
*/

/* Imprime a y b en vertical, una al lado de la otra: la cima arriba */

void	print_stacks(t_stack *a, t_stack *b)
{
	while (a || b)
	{
		if (a)
		{
			ft_printf("%d", a->value);
			a = a->next;
		}
		ft_printf("\t");
		if (b)
		{
			ft_printf("%d", b->value);
			b = b->next;
		}
		ft_printf("\n");
	}
	ft_printf("-\t-\na\tb\n\n");
}
