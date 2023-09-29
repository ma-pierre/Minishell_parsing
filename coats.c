#include "minishell_parse.h"

char *check_quotes(char *str)
{
	int	i;
	int	j;
	char c;

	i = 0;
	j = 0;
	while (str[i])
	{
		if(str[i] == '"' || str[i] == '\'')
		{
			j = 1;
			c = str[i];
			i++;
			while(str[i])
			{
				if(str[i] == c)
				{
					j = 0;
					break;
				}
				else
					str[i++] *= -1;
			}
		}
		else
			str[i] *= -1;
		i++;
	}
	if (j == 1)
		return (NULL);
	return (str);
}
//cette fonction passe tout les caractere en negatif afin de ne garder que les coats,
// si les coats sont mal fermes, elle return NULL, sinon elle return la string avec les *-1
//seuls les coats seront visible