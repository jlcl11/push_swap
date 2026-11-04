/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/11/04 12:00:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	record_op(t_flags *flags, int *counter, const char *name)
{
	(*counter)++;
	flags->total++;
	ft_printf("%s\n", name);
}
