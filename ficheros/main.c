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

/* Escribe Error por stderr, libera la pila y devuelve el código de salida */

static int	error_exit(t_stack **a)
{
	ft_putendl_fd("Error", 2);
	stack_clear(a);
	return (1);
}

/* Ejecuta el algoritmo de la estrategia elegida con las flags */

static void	run_strategy(t_stack **a, t_stack **b, t_strategy strategy)
{
	if (strategy == STRAT_SIMPLE)
		bubble_sort(a);
	else if (strategy == STRAT_MEDIUM)
		chunk_sort(a, b);
	else if (strategy == STRAT_COMPLEX)
		radix_sort(a, b);
	else
		adaptative_sort(a, b);
}

/*
** Sin números no se imprime nada, según el subject (también si solo hay
** flags). Si a ya está ordenada tampoco se hace ningún movimiento.
*/

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	t_flags	flags;
	int		first;

	a = NULL;
	b = NULL;
	first = parse_flags(argc, argv, &flags);
	if (first < 0)
		return (error_exit(&a));
	if (first == argc)
		return (0);
	if (!parse_args(argc - first, argv + first, &a))
		return (error_exit(&a));
	if (!is_sorted(a))
		run_strategy(&a, &b, flags.strategy);
	stack_clear(&a);
	stack_clear(&b);
	return (0);
}
