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

#include <beastlang/error.h>
#include <beastlang/lexer.h>
#include <beastlang/parser.h>
#include <beastlang/utils.h>

static void	node_push(node_t **nodes, node_t *node)
{
	node_t	*tmp;

	if (*nodes == NULL)
	{
		*nodes = node;
		return;
	}
	tmp = *nodes;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

static node_t	*node_pop(node_t **nodes)
{
	node_t	*tmp;

	tmp = *nodes;
	if (tmp == NULL)
		return (NULL);
	*nodes = tmp->next;
	return (tmp);
}

void	nodes_free_all(node_t **nodes)
{
	node_t	*tmp;

	while ((tmp = node_pop(nodes)) != NULL)
	{
		if (tmp->type == N_CALL)
			nodes_free_all(&(tmp->args));
		if (tmp->type == N_CALL || tmp->type == N_VAR || tmp->type == N_STR)
			free(tmp->u1.value);
		free(tmp);
	}
}


static node_t	*node_new(node_type_t type)
{
	node_t	*new;

	new = (node_t *)malloc(sizeof(node_t));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->args = NULL;
	new->next = NULL;
	return (new);
}

static node_t	*get_atom(token_t **stack)
{
	token_t	*tmp;
	node_t	*atom_node;

	tmp = token_pop(stack);
	if (tmp->type == T_IDENT)
	{
		atom_node = node_new(N_VAR);
		if (atom_node != NULL)
			atom_node->u1.value = strdup(tmp->value);
	}
	else if (tmp->type == T_STRING)
	{
		atom_node = node_new(N_STR);
		if (atom_node != NULL)
			atom_node->u1.value = strdup(tmp->value);
	}
	else if (tmp->type == T_NUMBER)
	{
		atom_node = node_new(N_NUMBER);
		if (atom_node != NULL)
			atom_node->u1.number = atoi(tmp->value);
	}
	else
	{
		tmp->next = *stack;
		*stack = tmp;
		return (NULL);
	}
	token_free(tmp);
	return (atom_node);
}

static node_t	*get_expr(token_t **stack)
{
	token_t	*tmp;
	node_t	*expr_node;
	node_t	*n_tmp;

	tmp = token_pop(stack);
	if (tmp->type != T_PARLEFT)
	{
		tmp->next = *stack;
		*stack = tmp;
		return (NULL);
	}
	token_free(tmp);
	tmp = token_pop(stack);
	if (tmp->type != T_IDENT)
	{
		token_free(tmp);
		return (NULL);
	}
	expr_node = node_new(N_CALL);
	if (expr_node == NULL)
	{
		token_free(tmp);
		return (NULL);
	}
	expr_node->u1.value = strdup(tmp->value);
	expr_node->args = NULL;
	token_free(tmp);
	while (*stack != NULL)
	{
		if ((n_tmp = get_expr(stack)) != NULL)
		{
			node_push(&(expr_node->args), n_tmp);
		}
		else if ((n_tmp = get_atom(stack)) != NULL)
		{
			node_push(&(expr_node->args), n_tmp);
		}
		else
		{
			tmp = token_pop(stack);
			if (tmp->type == T_PARRIGHT)
			{
				token_free(tmp);
				break;
			}
			token_free(tmp);
			return (NULL);
		}
	}
	return (expr_node);
}

void	parse(token_t **stack, node_t **nodes)
{
	node_t	*exp;

	while (*stack != NULL)
	{
		if ((exp = get_expr(stack)) == NULL)
		{
			error("\033[31mSyntax error\033[0m\n");
			break;
		}
		node_push(nodes, exp);
	}
}
