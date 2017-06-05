/*
 * Copyright (C) 2016  d0p1 <dopi-sama@hush.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>

#include <beastlang/lexer.h>
#include <beastlang/parser.h>
#include <beastlang/context.h>

node_t	*eval_expr(node_t *expr, context_t *ctx)
{
	function_t	*func;

	func = function_get(&(ctx->functions), expr->u1.value);
	if (func == NULL)
		return (NULL);
	return (func->fnc(expr->args, ctx));
}

int	eval(char *str)
{
	token_t		*tokens;
	node_t		*nodes;
	node_t		*tmp;
	context_t	*ctx;

	tokens = NULL;
	lex(str, &tokens);
	if (tokens == NULL)
		return (-1);
	nodes = NULL;
	parse(&tokens, &nodes);
	if (tokens != NULL || nodes == NULL)
	{
		tokens_free_all(&tokens);
		return (-1);
	}
	ctx = ctx_init();
	if (ctx == NULL)
		return (-1);
	tmp = nodes;
	while (tmp != NULL)
	{
		eval_expr(tmp, ctx);
		tmp = tmp->next;
	}
	nodes_free_all(&nodes);
	ctx_free(ctx);
	return (0);
}
