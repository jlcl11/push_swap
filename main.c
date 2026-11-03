/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 12:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 19:38:49 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	error_exit(t_stack **a)
{
	ft_putendl_fd("Error", 2);
	stack_clear(a);
	return (1);
}

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

void	display_bench_continue(t_flags *flags)
{
	ft_putnbr_fd(flags->sb, 2);
	ft_putstr_fd("  ss: ", 2);
	ft_putnbr_fd(flags->ss, 2);
	ft_putstr_fd("  pa: ", 2);
	ft_putnbr_fd(flags->pa, 2);
	ft_putstr_fd("  pb: ", 2);
	ft_putnbr_fd(flags->pb, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("[bench] ra: ", 2);
	ft_putnbr_fd(flags->ra, 2);
	ft_putstr_fd("  rb: ", 2);
	ft_putnbr_fd(flags->rb, 2);
	ft_putstr_fd("  rr: ", 2);
	ft_putnbr_fd(flags->rr, 2);
	ft_putstr_fd("  rra: ", 2);
	ft_putnbr_fd(flags->rra, 2);
	ft_putstr_fd("  rrb: ", 2);
	ft_putnbr_fd(flags->rrb, 2);
	ft_putstr_fd("  rrr: ", 2);
	ft_putnbr_fd(flags->rrr, 2);
	ft_putchar_fd('\n', 2);
}

void	display_bench(t_flags *flags)
{
	int	disord1;
	int	disord2;

	disord1 = (int)(flags->disorder * 100);
	disord2 = (int)(flags->disorder * 10000 - disord1 * 100);
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(disord1, 2);
	ft_putchar_fd('.', 2);
	if (disord2 < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd(disord2, 2);
	ft_putstr_fd("%\n", 2);
	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putstr_fd(flags->strag_name, 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(flags->complexity, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(flags->total, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_fd(flags->sa, 2);
	ft_putstr_fd("  sb: ", 2);
	display_bench_continue(flags);
}

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
