#include "push_swap.h"

static void	sort_three(t_stack **stack)
{
	int first;
	int second;
	int third;

	first = (*stack)->index;
	second = (*stack)->next->index;
	third = (*stack)->next->next->index;

	if (first > second && second < third && first < third)
		sa(stack);
	else if (first > second && second > third)
	{
		sa(stack);
		rra(stack);
	}
	else if (first > second && second < third && first > third)
		ra(stack);
	else if (first < second && second > third && first < third)
	{
		sa(stack);
		ra(stack);
	}
	else if (first < second && second > third && first > third)
		rra(stack);
}
void	adaptative_sort(t_stack **stack_a, t_stack **stack_b)
{
	double	disorder;
	int		size;

	disorder = compute_disorder(*stack_a);
	size = stack_size(*stack_a);
	index_list(*stack_a);
	if (size < 2 || !disorder)
		return ;
	if	(size == 2)
		sa(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (disorder < 0.2)
		bubble_sort(stack_a);
	else if (disorder >= 0.2 && disorder < 0.5)
		chunk_sort(stack_a, stack_b);
	else if (disorder >= 0.5)
		radix_sort(stack_a, stack_b);
}
