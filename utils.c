#include "push_swap.h"

void	ft_sort_int_tab(int *tab, int size)
{
	int	temp;
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i -1)
		{
			if (tab[j] > tab[j + 1])
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
void	sort_three_a(t_stack **stack)
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

void	sort_three_b(t_stack **stack)
{
	int first;
	int second;
	int third;

	first = (*stack)->index;
	second = (*stack)->next->index;
	third = (*stack)->next->next->index;

	if (first < second && second < third && first < third)
	{
		sb(stack);
		rrb(stack);
	}
	else if (first < second && second > third && first < third)
		rb(stack);
	else if (first > second && second < third && first < third)
		rrb(stack);
	else if (first < second && second > third && first > third)
		sb(stack);
	else if (first > second && second < third && first > third)
	{
		sb(stack);
		rb(stack);
	}
}
