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

#ifndef PARSER_H_
# define PARSER_H_

#include "lexer.h"

typedef enum
{
	N_CALL,
	N_VAR,
	N_STR,
	N_NUMBER
} node_type_t;

struct				node_s
{
	node_type_t		type;
	union
	{
		int		number;
		char		*value;
	} u1;
	struct node_s		*args;
	struct node_s		*next;
};

typedef struct node_s node_t;

void	parse(token_t **stack, node_t **nodes);
void	nodes_free_all(node_t **nodes);

#endif /* PARSER_H_ */
