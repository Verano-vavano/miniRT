#ifndef ERRORS_H
# define ERRORS_H

# include "libft.h"
# include "render.h"

bool	already_set_error(char set);
bool	invalid_range_error(char *set, char *lb, char *ub);
bool	too_many_args_error(char *set, char *req);
bool	malloc_error(char *set);

bool	float_convert_error(char c);
bool	float_too_many_digits(char c);

void	vec3_number_error(char *arg, char **xyz);
void	vec3_arg_error(char *arg, char **xyz);

bool	parsing_err(int argc, char **argv);

#endif
