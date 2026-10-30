/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunez-b <jnunez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 12:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/30 06:58:23 by jnunez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_stack
{
	int				value;
	int				index; // He añadido esto, pqq nos hace falta tener indice en el chunk_sort
	struct s_stack	*next;
}	t_stack;

t_stack	*stack_new(int value);
void	stack_push(t_stack **stack, t_stack *node);
void	stack_add_back(t_stack **stack, t_stack *node);
int		stack_size(t_stack *stack);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);
void	bubble_sort(t_stack **stack);
void	print_stacks(t_stack *a, t_stack *b);
double	compute_disorder(t_stack *stack);	//joseN ha hecho algo xd xd
void	index_list(t_stack *stack);
void	chunk_sort(t_stack **stack_a, t_stack **stack_b);
void	quick_sort(t_stack **stack_a, t_stack **stack_b);
void	quick_sort_a(t_stack **stack_a, t_stack **stack_b, int size);
void	quick_sort_b(t_stack **stack_a, t_stack **stack_b, int size);
void	ft_sort_int_tab(int *tab, int size);
void	sort_three_a(t_stack **stack);
void	sort_three_b(t_stack **stack);

#endif
