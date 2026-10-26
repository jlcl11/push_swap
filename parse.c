/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parse.c                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/23 16:00:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/26 12:00:00 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Libera el array que devuelve ft_split */

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*
** Valida cada palabra, la convierte y la añade al fondo de a.
** Devuelve 0 si alguna no es un número, se sale de int o falla malloc.
*/

static int	add_numbers(t_stack **a, char **nums)
{
	t_stack	*node;
	long	n;
	int		i;

	i = 0;
	while (nums[i])
	{
		if (!is_number(nums[i]))
			return (0);
		n = ft_atol(nums[i]);
		if (n > INT_MAX || n < INT_MIN)
			return (0);
		node = stack_new((int)n);
		if (!node)
			return (0);
		stack_add_back(a, node);
		i++;
	}
	return (1);
}

/*
** Recibe solo los argumentos de números (las flags ya se han saltado).
** Ejemplo: ./push_swap 3 "1 2" 4
** Cada argumento se parte por espacios con ft_split, así también se aceptan
** números entre comillas. El primer número queda en la cima de la pila.
** Un argumento vacío ("" o "   ") es un error.
** Devuelve 1 si todo es correcto y no hay repetidos, 0 si no.
*/

int	parse_args(int count, char **args, t_stack **a)
{
	char	**nums;
	int		i;

	i = 0;
	while (i < count)
	{
		nums = ft_split(args[i], ' ');
		if (!nums)
			return (0);
		if (!nums[0] || !add_numbers(a, nums))
		{
			free_split(nums);
			return (0);
		}
		free_split(nums);
		i++;
	}
	return (!has_duplicates(*a));
}
