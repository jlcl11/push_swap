/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 12:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 14:21:49 by jnunez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_flag(const char *arg, const char *flag)
{
	return (ft_strncmp(arg, flag, ft_strlen(flag) + 1) == 0);
}

static int	set_strategy(const char *arg, t_flags *flags, int *chosen)
{
	if (*chosen)
		return (0);
	if (is_flag(arg, "--simple"))
		flags->strategy = STRAT_SIMPLE;
	else if (is_flag(arg, "--medium"))
		flags->strategy = STRAT_MEDIUM;
	else if (is_flag(arg, "--complex"))
		flags->strategy = STRAT_COMPLEX;
	else if (is_flag(arg, "--adaptive"))
		flags->strategy = STRAT_ADAPTIVE;
	else
		return (0);
	*chosen = 1;
	return (1);
}

static void	init_bench_count(t_flags *flags)
{
	flags->disorder = 0;
	flags->pa = 0;
	flags->pb = 0;
	flags->sa = 0;
	flags->sb = 0;
	flags->ss = 0;
	flags->ra = 0;
	flags->rb = 0;
	flags->rr = 0;
	flags->rra = 0;
	flags->rrb = 0;
	flags->rrr = 0;
	flags->total = 0;
	flags->strag_name = NULL;
	flags->complexity = NULL;
}

static void	set_description(t_flags *flags)
{
	if (flags->strategy == STRAT_SIMPLE)
	{
		flags->strag_name = "Simple";
		flags->complexity = "O(n²)";
	}
	else if (flags->strategy == STRAT_MEDIUM)
	{
		flags->strag_name = "Medium";
		flags->complexity = "O(n√n)";
	}
	else if (flags->strategy == STRAT_COMPLEX)
	{
		flags->strag_name = "Complex";
		flags->complexity = "O(n log n)";
	}
	else
		flags->strag_name = "Adaptive";
}

int	parse_flags(int argc, char **argv, t_flags *flags)
{
	int	chosen;
	int	i;

	flags->strategy = STRAT_ADAPTIVE;
	flags->bench = 0;
	chosen = 0;
	i = 1;
	init_bench_count(flags);
	while (i < argc && ft_strncmp(argv[i], "--", 2) == 0)
	{
		if (is_flag(argv[i], "--bench"))
		{
			if (flags->bench)
				return (-1);
			flags->bench = 1;
		}
		else if (!set_strategy(argv[i], flags, &chosen))
			return (-1);
		i++;
	}
	set_description(flags);
	return (i);
}
