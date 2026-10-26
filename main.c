/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/16 12:00:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/23 17:36:43 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

/* Escribe Error por stderr, libera la pila y devuelve el código de salida */

static int	error_exit(t_stack **a)
{
	ft_putendl_fd("Error", 2);
	stack_clear(a);
	return (1);
}

/* Sin argumentos no se imprime nada, según el subject */

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (0);
	if (!parse_args(argc, argv, &a))
		return (error_exit(&a));
	ft_printf("ANTES:\n");
	print_stacks(a, b);
	bubble_sort(&a);
	ft_printf("\nDESPUES (bubble sort):\n");
	print_stacks(a, b);
	stack_clear(&a);
	return (0);
}
