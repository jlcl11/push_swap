/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/16 12:00:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/16 13:48:54 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Imprime a y b en vertical, una al lado de la otra: la cima arriba */

static void	print_stacks(t_stack *a, t_stack *b)
{
	while (a || b)
	{
		if (a)
		{
			ft_putnbr_fd(a->value, 1);
			a = a->next;
		}
		ft_putstr_fd("\t", 1);
		if (b)
		{
			ft_putnbr_fd(b->value, 1);
			b = b->next;
		}
		ft_putstr_fd("\n", 1);
	}
	ft_putstr_fd("-\t-\na\tb\n\n", 1);
}

/* Libera todos los nodos de la pila */

static void	free_stack(t_stack *stack)
{
	t_stack	*tmp;

	while (stack)
	{
		tmp = stack->next;
		free(stack);
		stack = tmp;
	}
}

/*
** Ejemplo: ./push_swap 3 1 2
** Cada argumento se convierte en un nodo y se añade al fondo,
** así el primer argumento queda en la cima de la pila.
*/

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		i;

	a = NULL;
	b = NULL;
	i = 1;
	while (i < argc)
	{
		stack_add_back(&a, stack_new(ft_atoi(argv[i])));
		i++;
	}
	print_stacks(a, b);
	sa(&a);
	print_stacks(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
