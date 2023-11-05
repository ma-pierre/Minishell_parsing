/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:17 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/05 17:06:05 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"

char	*dollar_qm(void)
{
	char	*var;

	var = malloc(2);
	if (!var)
		return (NULL);
	var[0] = '0' + DQM;
	var[1] = '\0';
	return (var);
}

char	*negative_doublequotes(char *line)
{
	int		i;
	char	c;
	
	i = 0;
	while(line[i] != '\0')
	{
		if(line[i] == '"')
		{
			c = line[i++]; 
			while (line[i] && line[i] != c)
				line[i++] *= -1;
		}
		i++;
	}
	return (line);
}

char	*rmv_spaces_quotes(char *line)
{
    char	*new_line;
	int		i;
	int		j;
	char	prev_char;
	
	new_line = malloc(strlen(line) + 1);
    if (!new_line)
		return NULL;
	i = 0;
	j = 0;
    prev_char = ' ';
	while (line[i] && is_space(line[i]))
		i++;
    while (line[i])
	{
        if (is_space(line[i]))
		{
            if (!is_space(prev_char))
                new_line[j++] = ' ';
		}
        else if (line[i] != '\"' && line[i] != '\'')
		{
            new_line[j++] = line[i];
		}
		prev_char = line[i++];
    }
    if (j > 0 && is_space(new_line[j - 1]))
        j--;
    new_line[j] = '\0';
    return (new_line);
}

