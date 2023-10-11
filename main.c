#include "minishell_parse.h"

void handle_sigint(int sig) 
{
    (void)sig;
    write(1, "\nMinishell> ", 12);
}

void handle_eof()
{
    write(1, "\nExiting Minishell...\n", 23);
    exit(0);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sa.sa_flags = SA_RESTART | SA_RESETHAND;
    sigaction(SIGINT, &sa, NULL);

    char *line;
    while (1) 
    {
        //printf(MAGENTA "Minishell> " RESET);
        line = readline("Minishell> ");
        if (!line)
        {
            handle_eof();
            continue;
        }
		if (line && *line)
    		add_history(line);
		if (line)
		{
			if (!check_quotes(line))
			{
				printf("quote error\n");
				free(line);
				continue;
			}
			if (!syntax_parse(line))
			{
				free(line);
				continue;
			}
			printf("R.A.S SUR L'ENTREE SUIVANTE :  %s\n", line);
		}
       	free(line);
	}
}

