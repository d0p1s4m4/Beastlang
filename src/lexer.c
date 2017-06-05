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
#include <beastlang/lexer.h>
#include <beastlang/error.h>
#include <beastlang/utils.h>

token_t	*token_pop(token_t **stack)
{
	token_t	*tmp;

	tmp = *stack;
	if (tmp == NULL)
		return (NULL);
	*stack = tmp->next;
	return (tmp);
}

void	token_free(token_t *token)
{
	free(token->value);
	free(token);
}

void	tokens_free_all(token_t	**stack)
{
	token_t	*tmp;

	while ((tmp = token_pop(stack)) != NULL)
		token_free(tmp);
}

static token_t	*token_new(char *str, token_type_t type)
{
	token_t	*tok;

	tok = (token_t *)malloc(sizeof(token_t));
	if (tok == NULL)
		return (NULL);
	tok->value = str;
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

static void	token_push(token_t **stack, token_t *token)
{
	token_t	*tmp;

	if (*stack == NULL)
	{
		*stack = token;
		return;
	}
	tmp = *stack;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = token;
}

static int	get_par(char *str, token_t **token)
{
	if (str[0] == '(')
	{
		*token = token_new(strdup("("), T_PARLEFT);
		return (1);
	}
	else if (str[0] == ')')
	{
		*token = token_new(strdup(")"), T_PARRIGHT);
		return (1);
	}
	return (0);
}

static int	get_ident(char *str, token_t **token)
{
	int	i;
	char	*ident;

	if (!(*str >= 'a' && *str <= 'z') && !(*str >= 'A' && *str <= 'Z') && *str != '_')
		return (0);
	for (i = 0; str[i] != ' ' && str[i] != '(' && str[i] != ')' && str[i] != '\0'; i++);
	ident = (char *)malloc(sizeof(char) * (i + 1));
	if (ident == NULL)
		return (0);
	strncpy(ident, str, i);
	ident[i] = '\0';
	*token = token_new(ident, T_IDENT);
	return (i);
}

static int	get_number(char *str, token_t **token)
{
	int	i;
	char	*number;

	if (!(*str >= '0' && *str <= '9'))
		return (0);
	for (i = 0; str[i] >= '0' && str[i] <= '9'; i++);
	number = (char *)malloc(sizeof(char) * (i + 1));
	if (number == NULL)
		return (0);
	strncpy(number, str, i);
	number[i] = '\0';
	*token = token_new(number, T_NUMBER);
	return (i);
}

static int	get_string(char *str, token_t **token)
{
	int	i;
	char	*string;

	if (*str != '"')
		return (0);
	for (i = 1; str[i] != '"' && str[i] != '\0'; i++);
	string = (char *)malloc(sizeof(char) * (i + 1));
	strncpy(string, str + 1, i - 1);
	string[i] = '\0';
	*token = token_new(string, T_STRING);
	return (i + 1);
}

static int	ignore_unsignifiant_char(char *str)
{
	int	i;

	for (i = 0; str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'; i++);
	return (i);
}

void	lex(char *str, token_t **stack)
{
	token_t	*current_token;
	int	ret;

	if (*str == '\0')
		return;
	if ((ret = get_par(str, &current_token)) > 0)
		token_push(stack, current_token);
	else if ((ret = get_ident(str, &current_token)) > 0)
		token_push(stack, current_token);
	else if ((ret = get_string(str, &current_token)) > 0)
		token_push(stack, current_token);
	else if ((ret = get_number(str, &current_token)) > 0)
		token_push(stack, current_token);
	else
		error("\033[31mUnknown token\033[0m\n");
	ret += ignore_unsignifiant_char(str + ret);
	lex(str + ret, stack);
}
