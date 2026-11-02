/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   push_swap.h                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/16 12:00:00 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/23 17:08:08 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"

typedef enum e_strategy
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX
}	t_strategy;

typedef struct s_flags
{
	t_strategy	strategy;
	int			bench;
}	t_flags;

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

/* stack.c */
t_stack	*stack_new(int value);
void	stack_push(t_stack **stack, t_stack *node);
void	stack_add_back(t_stack **stack, t_stack *node);
int		stack_size(t_stack *stack);
void	stack_clear(t_stack **stack);

/* flags.c, parse.c, parse_utils.c */
int		parse_flags(int argc, char **argv, t_flags *flags);
int		parse_args(int count, char **args, t_stack **a);
int		is_number(const char *str);
long	ft_atol(const char *str);
int		has_duplicates(t_stack *stack);

/* operations/ */
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

/* bubble_algorithm.c */
int		is_sorted(t_stack *stack);
void	bubble_sort(t_stack **stack);

/* compute_disorder.c */
double	compute_disorder(t_stack *stack);

/* chunck_algorithm.c */
void	index_list(t_stack *stack);
void	chunk_sort(t_stack **stack_a, t_stack **stack_b);

/* radix_sort_algorithm.c */
void	radix_sort(t_stack **stack_a, t_stack **stack_b);

/* adaptative_algorithm.c */
void	adaptative_sort(t_stack **stack_a, t_stack **stack_b);

/* debug.c */
void	print_stacks(t_stack *a, t_stack *b);

#endif
