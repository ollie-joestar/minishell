
#include "minishell.h"

// Identify a pipe (`|`)
int	check_pipe_symbol(char **input_start, char **input_end)
{
	if (**input_start == '|')
	{
		*input_end += 1;
		return (PIPE);
	}
	return (0);
}

// Moves the pointer to the end of the token, skipping over non-special characters
char	*find_token_end(char *input)
{
	while (*input && !is_special_char(*input))
		input++;
	return (input);
}

// Resets the end pointer based on whether a quoted string is fully closed
void	reset_token_end(char *input_start, char **input_end, char *quote_ptr, char *token_end)
{
	if (quote_ptr != token_end)
		*input_end = input_start;
	else
		*input_end = token_end;
}
