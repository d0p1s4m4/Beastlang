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

#ifndef LEXER_H_
# define LEXER_H_

typedef enum
{
	T_PARLEFT,
	T_PARRIGHT,
	T_IDENT,
	T_NUMBER,
	T_STRING
} token_type_t;

struct			token_s
{
	token_type_t	type;
	char		*value;
	struct token_s	*next;
};
typedef struct token_s token_t;


void	lex(char *str, token_t **stack);
token_t	*token_pop(token_t **stack);
void	token_free(token_t *token);
void	tokens_free_all(token_t	**stack);

#endif /* !LEXER_H_ */
