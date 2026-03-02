/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 01:10:01 by kyanagis          #+#    #+#             */
/*   Updated: 2025/08/12 00:53:34 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_two(t_node **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a);
}

void	sort_small(t_node **stack_a)
{
	size_t	n;

	n = list_size(*stack_a);
	if (n <= 1)
		return ;
	if (n == 2)
		sort_two(stack_a);
	else
		sort_three(stack_a);
}

void	sort_three(t_node **stack_a)
{
	int	x;
	int	y;
	int	z;

	if (!*stack_a || !(*stack_a)->next || !(*stack_a)->next->next)
		return ;
	x = (*stack_a)->value;
	y = (*stack_a)->next->value;
	z = (*stack_a)->next->next->value;
	if (x > y && y < z && x < z)
		sa(stack_a);
	else if (x > y && y > z)
	{
		sa(stack_a);
		rra(stack_a);
	}
	else if (x > y && y < z && x > z)
		ra(stack_a);
	else if (x < y && y > z && x < z)
	{
		sa(stack_a);
		ra(stack_a);
	}
	else if (x < y && y > z && x > z)
		rra(stack_a);
}
