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
#include <unistd.h>

#include "error.h"
#include "eval.h"

int	my_usage(char *str)
{
	fprintf(stderr, "\033[31mError usage: %s <program_file>\033[0m\n", str);
	return (EXIT_FAILURE);
}

int	run_program(char *prg_name)
{
	FILE	*source;
	long	size;
	char	*content;
	int	ret;

	if (access(prg_name, R_OK) != 0)
		return (error("\033[31mError %s no such file\033[0m\n", prg_name));
	source = fopen(prg_name, "r");
	if (source == NULL)
		return (error("\033[31mError can't open %s\033[0m\n", prg_name));
	fseek(source, 0, SEEK_END);
	size = ftell(source);
	fseek(source, 0, SEEK_SET);
	content = (char *)malloc(sizeof(char) * (size + 1));
	fread(content, size, 1, source);
	fclose(source);
	content[size] = '\0';
	ret = eval(content);
	free(content);
	return (ret);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		return (my_usage(argv[0]));
	for (i = 1; i < argc; i++)
	{
		if (run_program(argv[i]) != 0)
			error("\033[31m%s exit with error code\033[0m\n", argv[i]);
	}
	return (EXIT_SUCCESS);
}
