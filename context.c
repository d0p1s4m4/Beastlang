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
#include <string.h>

#include "context.h"
#include "utils.h"
#include "builtin.h"

variable_t	*variable_new(char *name, variable_type_t type, int number, char *value)
{
	variable_t	*new;

	new = (variable_t *)malloc(sizeof(variable_t));
	if (new == NULL)
		return (NULL);
	new->name = strdup(name);
	new->type = type;
	if (type == V_STRING)
		new->content.value = strdup(value);
	else
		new->content.number = number;
	return (new);
}


void	variable_push(variable_t **stack, char *name, variable_type_t type,
		int number, char *value)
{
	variable_t	*tmp;

	tmp = *stack;
	while (tmp != NULL)
	{
		if (strcmp(name, tmp->name) == 0)
		{
			tmp->type = type;
			if (type == V_STRING)
				tmp->content.value = strdup(value);
			else
				tmp->content.number = number;
			return;
		}
		tmp = tmp->next;
	}
	tmp = variable_new(name, type, number, value);
	if (tmp == NULL)
		return;
	tmp->next = *stack;
	*stack = tmp;
}

static variable_t	*variable_pop(variable_t **stack)
{
	variable_t	*tmp;

	tmp = *stack;
	if (tmp == NULL)
		return (NULL);
	*stack = tmp->next;
	return (tmp);
}

variable_t	*variable_get(variable_t **stack, char *name)
{
	variable_t	*tmp;

	tmp = *stack;
	if (tmp == NULL)
		return (NULL);
	while (tmp != NULL)
	{
		if (strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	variables_free_all(variable_t **stack)
{
	variable_t	*tmp;

	while ((tmp = variable_pop(stack)) != NULL)
	{
		if (tmp->type == V_STRING)
			free(tmp->content.value);
		free(tmp->name);
		free(tmp);
	}
}

function_t	*function_new(char *name, node_t *(*fnc)(node_t *, context_t *))
{
	function_t	*tmp;

	tmp = (function_t *)malloc(sizeof(function_t));
	if (tmp == NULL)
		return (NULL);
	tmp->name = strdup(name);
	tmp->fnc = fnc;
	return (tmp);
}

void	function_push(function_t **stack, char	*name, node_t *(*fnc)(node_t *, context_t *))
{
	function_t	*tmp;

	tmp = function_new(name, fnc);
	if (tmp == NULL)
		return;
	tmp->next = *stack;
	*stack = tmp;
}

static function_t	*function_pop(function_t **stack)
{
	function_t	*tmp;

	tmp = *stack;
	if (tmp == NULL)
		return (NULL);
	*stack = tmp->next;
	return (tmp);
}

void	functions_free_all(function_t **stack)
{
	function_t	*tmp;

	while ((tmp = function_pop(stack)) != NULL)
	{
		free(tmp->name);
		free(tmp);
	}
}

function_t	*function_get(function_t **stack, char *name)
{
	function_t	*tmp;

	tmp = *stack;
	while (tmp != NULL)
	{
		if (strcmp(tmp->name, name) == 0)
		{
			return (tmp);
		}
	}
	return (NULL);
}

context_t	*ctx_init()
{
	context_t	*ctx;

	ctx = (context_t *)malloc(sizeof(context_t));
	if (ctx == NULL)
		return (NULL);
	ctx->variables = NULL;
	ctx->functions = NULL;
	variable_push(&(ctx->variables), "__VERSION__", V_NUMBER, 0X1, NULL);
	variable_push(&(ctx->variables), "_NL_", V_STRING, 0, "\n");
	function_push(&(ctx->functions), "echo", builtin_echo);
	return (ctx);
}

void	ctx_free(context_t *ctx)
{
	variables_free_all(&(ctx->variables));
	functions_free_all(&(ctx->functions));
	free(ctx);
}
