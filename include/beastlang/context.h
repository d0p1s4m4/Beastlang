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

#ifndef CONTEXT_H_
# define CONTEXT_H_

#include "parser.h"

typedef enum
{
	V_NUMBER,
	V_STRING
} variable_type_t;

typedef struct function_s function_t;
typedef struct variable_s variable_t;

typedef struct
{
	variable_t	*variables;
	function_t	*functions;
} context_t;

struct			variable_s
{
	char			*name;
	variable_type_t		type;
	union {
		int		number;
		char		*value;
	} content;
	struct variable_s	*next;
};

struct				function_s
{
	char			*name;
	node_t			*(*fnc)(node_t *, context_t *);
	struct function_s	*next;
};

context_t	*ctx_init();
function_t	*function_get(function_t **stack, char *name);
variable_t	*variable_get(variable_t **stack, char *name);
void	ctx_free(context_t *ctx);

#endif /* CONTEXT_H_ */
