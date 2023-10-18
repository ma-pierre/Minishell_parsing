#include "minishell_parse.h"

void handle_sigint(int sig) 
{
    (void)sig;
    write(1, "\nMinishell> ", 12);
}

void ft_exit()
{
    write(1, "\nExit\n", 6);
    exit(0);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

	// printf("%s\n", env[0]);
	// printf("%s\n", env[1]);
	// printf("%s\n", env[2]);
	// printf("%s\n", env[3]);

    char *line;
    while (1) 
	{
        //printf(MAGENTA "Minishell> " RESET);
        line = readline("Minishell> ");
		if (!line)
		{
			ft_exit();
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
				continue ;
			}
			if (!syntax_parse(line))
			{
				free(line);
				continue ;
			}
			split_env(line);
		}
       	free(line);
	}
}

