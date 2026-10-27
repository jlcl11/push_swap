
#include "push_swap.h"

double	compute_disorder(t_stack *stack)
{
	t_stack *i;
	t_stack	*j;
	int	pairs;
	int	mistakes;

	pairs = 0;
	mistakes = 0;
	i = stack;
	while (i)
	{
		j = i->next;
		if (j)
		{
			pairs++;
			if (i->value > j->value)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	if (mistakes == 0)
		return (0.0);
	return ((double)mistakes / pairs);
}
