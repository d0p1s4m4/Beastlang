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

#include <stdio.h>
#include "parser.h"
#include "context.h"
#include "eval.h"

node_t	*builtin_echo(node_t *args, context_t *ctx)
{
	node_t		*tmp;
	node_t		*iterator;
	variable_t	*var;

	if (args == NULL)
		printf("(NULL)");
	tmp = args;
	iterator = args;
	while (tmp != NULL)
	{
		if (tmp->type == N_CALL)
			tmp = eval_expr(tmp, ctx);

		if (tmp->type == N_STR)
		{
			printf(tmp->u1.value);
		}
		else if (tmp->type == N_NUMBER)
		{
			printf("%d", tmp->u1.number);
		}
		else if (tmp->type == N_VAR)
		{
			var = variable_get(&(ctx->variables), tmp->u1.value);
			if (var == NULL)
				printf("(NULL)");
			else if (var->type == V_STRING)
				printf(var->content.value);
			else
				printf("%d", var->content.number);
		}
		tmp = iterator->next;
		iterator = iterator->next;
	}
	return (NULL);
}

