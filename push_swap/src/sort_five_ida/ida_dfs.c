/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ida_dfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 02:18:42 by kyanagis          #+#    #+#             */
/*   Updated: 2025/08/26 02:18:43 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_five.h"

static int	dfs(t_state *now, int g, t_ida_ctx *ctx);
static int	explore(t_state *now, int g, int op, t_ida_ctx *ctx);

static int	explore(t_state *now, int g, int op, t_ida_ctx *ctx)
{
	t_state	next;
	int		t;

	if ((g && inverse_op(op) == ctx->path[g - 1]) || (op == OP_PA
			&& !now->len_b) || (op == OP_PB && !now->len_a))
		return (INT_MAX);
	if ((op == OP_SA || op == OP_RA || op == OP_RRA) && now->len_a == 0)
		return (INT_MAX);
	if (op == OP_SA && now->len_a < 2)
		return (INT_MAX);
	next = *now;
	exec_op(&next, op);
	ctx->path[g] = op;
	t = dfs(&next, g + 1, ctx);
	if (t == FOUND)
		return (FOUND);
	return (t);
}

static int	dfs(t_state *now, int g, t_ida_ctx *ctx)
{
	int	f;
	int	min;
	int	op;
	int	t;

	f = g + inv_heuristic(now);
	if (f > ctx->bound)
		return (f);
	if (is_goal(now))
	{
		ctx->path[g] = -1;
		return (FOUND);
	}
	min = INT_MAX;
	op = -1;
	while (++op < OP_CNT)
	{
		t = explore(now, g, op, ctx);
		if (t == FOUND)
			return (FOUND);
		if (t < min)
			min = t;
	}
	return (min);
}

int	ida_search(t_state *root, int bound, int *path)
{
	t_ida_ctx	ctx;

	ctx.bound = bound;
	ctx.path = path;
	return (dfs(root, 0, &ctx));
}
