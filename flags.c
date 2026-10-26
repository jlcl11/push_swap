/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   flags.c                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/26 12:00:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/26 12:00:00 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Devuelve 1 si arg es exactamente flag (el +1 compara también el '\0') */

static int	is_flag(const char *arg, const char *flag)
{
	return (ft_strncmp(arg, flag, ft_strlen(flag) + 1) == 0);
}

/*
** Guarda la estrategia de un selector (--simple, --medium...).
** Devuelve 0 si arg no es un selector o si ya se había elegido uno.
*/

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

/*
** Lee las flags que van antes de los números, en cualquier orden:
**   ./push_swap --bench --simple 3 2 1
** Sin selector se usa --adaptive. Una flag desconocida, repetida o dos
** selectores a la vez son un error.
** Devuelve el índice del primer número en argv, o -1 si hay error.
*/

int	parse_flags(int argc, char **argv, t_flags *flags)
{
	int	chosen;
	int	i;

	flags->strategy = STRAT_ADAPTIVE;
	flags->bench = 0;
	chosen = 0;
	i = 1;
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
	return (i);
}
