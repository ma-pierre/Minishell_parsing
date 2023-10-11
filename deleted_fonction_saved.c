#include "minishell_parse.h"

/*premier main tout basique */int	main(void)
{
	char *input;

	input = readline(" MinishellDEREADLINE> ");
	if (input)
	{
		if (!check_quotes(input))
			return(printf("quote error\n"), 1);
		if (!syntax_parse(input))
			return(1);
		printf("%s\n", input);
		free(input);
	}
	return (0);
}