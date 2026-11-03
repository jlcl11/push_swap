/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 12:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/03 14:21:13 by jnunez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include "lib/libft/libft.h"
# include "lib/printf/ft_printf.h"

typedef enum e_strategy
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX
}	t_strategy;

typedef struct s_flags
{
	double		disorder;
	int			pa;
	int			pb;
	int			sa;
	int			sb;
	int			ss;
	int			ra;
	int			rb;
	int			rr;
	int			rra;
	int			rrb;
	int			rrr;
	int			total;
	char		*strag_name;
	char		*complexity;
	t_strategy	strategy;
	int			bench;
}	t_flags;

typedef struct s_chunk
{
	int	start;
	int	end;
}	t_chunk;

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

t_stack	*stack_new(int value);
void	stack_push(t_stack **stack, t_stack *node);
void	stack_add_back(t_stack **stack, t_stack *node);
int		stack_size(t_stack *stack);
void	stack_clear(t_stack **stack);

int		parse_flags(int argc, char **argv, t_flags *flags);
int		parse_args(int count, char **args, t_stack **a);
int		is_number(const char *str);
long	ft_atol(const char *str);
int		has_duplicates(t_stack *stack);

void	sa(t_stack **a, t_flags *flags);
void	sb(t_stack **b, t_flags *flags);
void	ss(t_stack **a, t_stack **b, t_flags *flags);
void	pa(t_stack **a, t_stack **b, t_flags *flags);
void	pb(t_stack **a, t_stack **b, t_flags *flags);
void	ra(t_stack **a, t_flags *flags);
void	rb(t_stack **b, t_flags *flags);
void	rr(t_stack **a, t_stack **b, t_flags *flags);
void	rra(t_stack **a, t_flags *flags);
void	rrb(t_stack **b, t_flags *flags);
void	rrr(t_stack **a, t_stack **b, t_flags *flags);

int		is_sorted(t_stack *stack);
void	selection_sort(t_stack **a, t_stack **b, t_flags *flags);

double	compute_disorder(t_stack *stack);

void	index_list(t_stack *stack);
void	chunk_sort(t_stack **stack_a, t_stack **stack_b, t_chunk *chunky,
			t_flags *flags);

void	radix_sort(t_stack **stack_a, t_stack **stack_b, t_flags *flags);

void	adaptative_sort(t_stack **stack_a, t_stack **stack_b, t_chunk *chunky,
			t_flags *flags);
void	sort_three(t_stack **stack, t_flags *flags);

#endif
