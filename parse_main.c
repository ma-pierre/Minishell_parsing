#include "minishell_parse.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\nMinishell> ", 12);
}

void	ft_exit(void)
{
	write(1, "\nExit\n", 6);
	exit(0);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	char				*line;
	char				*tmp;
	//char				*hdoc;
	char				**cmds;
	t_cmds				*data_exec;
	int					i;
	(void)ac;
	(void)av;
	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	// printf("%s\n", env[0]);
	// printf("%s\n", env[1]);
	// printf("%s\n", env[2]);
	// printf("%s\n", env[3]);
	//hdoc = NULL;
	cmds = NULL;

	while (1)
	{
		// printf(MAGENTA "Minishell> " RESET);
		line = readline("Minishell> ");
		tmp = ft_strdup(line);
		if (!tmp)
		{
			ft_exit();
			continue ;
		}
		if (tmp && *tmp)
			add_history(tmp);
		if (tmp)
		{
			tmp = check_quotes(tmp);
			if (!tmp)
			{
				printf("quote error\n");
				continue ;
			}
			printf("AFTER QUOTES = %s \n", tmp);
			if (!syntax_parse(tmp))
			{
				free(tmp);
				continue ;
			}
			while (-1 != find_pos_dollar(tmp))
			{
            char *new_tmp = split_env(tmp);
            if (new_tmp == NULL) {
                fprintf(stderr, "Failed to expand environment variables.\n");
                free(tmp);
                break; // Sortez de la boucle si l'expansion échoue.
            }
            if (tmp != new_tmp) { // Si une nouvelle chaîne a été allouée, libérez l'ancienne.
                free(tmp);
            }
            tmp = new_tmp;
        }
			// if(find_heredoc(line))
			//{
			//	hdoc = find_multi_heredoc(line);
			//}
			tmp = ft_positive(tmp);
			cmds = line_to_tab(tmp);
			//ENVOYER A LA PLACE DE LINE  LA LIGNE aVEc -1 au lieu des pipes;
			data_exec = tab_to_struct(cmds);
			if (!data_exec)
			{
				free(tmp);
				//GERER LERREUR
				return (0);
			}
			i = 0;
			while (data_exec[i].cmd)
			{
				printf("TAB %d ======= %s\n", i, data_exec[i].cmd);
				i++;
			}
		}
		free(tmp);
	}
}
