#include "minishell_parse.h"

int	main(void)
{
	char *input;

	input = readline("Minishell>");
	if (input)
	{
		input = check_quotes(input);
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
