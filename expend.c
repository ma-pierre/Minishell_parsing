#include "minishell_parse.h"

int	find_nb_dollar(char *str)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while(str[i])
	{
		if(str[i] == '$')
			d += 1;
		i++;
	}
	return (d);
}

char *split_env(char *str)
{
	int c;
	int i;
	char *before;
	char *to_expend;
	char *after;
	char *new;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (str[i])
			{

			}
		}

	}
}
