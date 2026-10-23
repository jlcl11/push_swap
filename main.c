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

/* Escribe Error por stderr, libera la pila y devuelve el código de salida */

static int	error_exit(t_stack *a)
{
	ft_putstr_fd("Error\n", 2);
	free_stack(a);
	return (1);
}

/*
** Ejemplo: ./push_swap 3 1 2
** Cada argumento se valida, se convierte en un nodo y se añade al fondo,
** así el primer argumento queda en la cima de la pila.
*/

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	t_stack	*node;
	long	n;
	int		i;
	int		j;

	a = NULL;
	b = NULL;
	if (argc < 2)
	{
		ft_printf("Error");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		if (!argv[i][j])
			return (error_exit(a));
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (error_exit(a));
			j++;
		}
		n = ft_atoi(argv[i]);
		if (n > INT_MAX || n < INT_MIN)
			return (error_exit(a));
		node = stack_new((int) n);
		if (!node)
			return (error_exit(a));
		stack_add_back(&a, node);
		i++;
	}
	if (has_duplicates(a))
		return (error_exit(a));
	ft_putstr_fd("ANTES:\n", 1);
	print_stacks(a, b);
	bubble_sort(&a);
	ft_putstr_fd("\nDESPUES (bubble sort):\n", 1);
	print_stacks(a, b);
	free_stack(a);
	return (0);
}
