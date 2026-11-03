/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 12:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 17:44:05 by jnunez-b         ###   ########.fr       */
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

static void	run_strategy(t_stack **a, t_stack **b, t_chunk *chunky,
	t_flags *flags)
{
	if (flags->strategy == STRAT_SIMPLE)
		selection_sort(a, b, flags);
	else if (flags->strategy == STRAT_MEDIUM)
		chunk_sort(a, b, chunky, flags);
	else if (flags->strategy == STRAT_COMPLEX)
		radix_sort(a, b, flags);
	else
		adaptative_sort(a, b, chunky, flags);
}

void	display_bench(t_flags *flags)
{
	int	disord1;
	int	disord2;

	disord1 = (int)(flags->disorder * 100);
	disord2 = (int)(flags->disorder * 10000 - disord1 * 100);
	ft_printf_error("[bench] ");
	ft_printf_error("disorder: %d.%d\n", disord1, disord2);
	ft_printf_error("[bench] ");
	ft_printf_error("strategy: %s / %s\n", flags->strag_name, flags->complexity);
	ft_printf_error("[bench] ");
	ft_printf_error("total_ops: %d\n", flags->total);
	ft_printf_error("[bench] ");
	ft_printf_error("sa: %d  sb: %d  ss: %d  ", flags->sa, flags->sb,flags->ss);
	ft_printf_error("pa: %d  pb: %d\n", flags->pa, flags->pb);
	ft_printf_error("[bench] ");
	ft_printf_error("ra: %d  rb: %d  rr: %d  ", flags->ra, flags->rb,flags->rr);
	ft_printf_error("rra: %d  rrb: %d  rrr: %d\n", flags->rra, flags->rrb,
		flags->rrr);
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
	t_chunk	chunky;
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
		run_strategy(&a, &b, &chunky, &flags);
	if (flags.bench)
		display_bench(&flags);
	stack_clear(&a);
	stack_clear(&b);
	return (0);
}
