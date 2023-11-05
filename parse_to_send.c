/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_send.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:14 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/05 17:30:31 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"

int	find_nbcmd(char *str)
{
	int	i;
	int	nbcmd;

	i = 0;
	nbcmd = 1;
	while (str[i])
	{
		if (str[i] == '|')
			nbcmd += 1;
		i++;
	}
	return (nbcmd);
}
int	find_next_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (i);
		i++;
	}
	return (-1);
}

t_cmds	*line_to_structs(char *line)
{
	int		nbcmd;
	int		start;
	int		end;
	int		i;
	t_cmds	*struct_cmds;
	char	*cleaned_split;
	char	*split;
	
	nbcmd = find_nbcmd(line);
	start = 0;
	end = 0;
	i = 0;
	struct_cmds = malloc(sizeof(t_cmds) * (nbcmd + 1));
	if (!struct_cmds)
		return (NULL);
	while ((end = find_next_pipe(line + start)) != -1)
    {
        split = ft_strndup(line + start, end);
        if (!split)
        {
            // Gérer l'erreur.
            // Libérer la mémoire allouée jusqu'à présent avant de retourner NULL.
            while (i > 0) free(struct_cmds[--i].cmd);
            	free(struct_cmds);
            return (NULL);
        }
        cleaned_split = rmv_spaces_quotes(split);
        	free(split);
        if (!cleaned_split)
        {
            // Gérer l'erreur.
            // Libérer la mémoire allouée jusqu'à présent avant de retourner NULL.
            while (i > 0) free(struct_cmds[--i].cmd);
            	free(struct_cmds);
            return NULL;
        }
        struct_cmds[i].cmd = cleaned_split; 
        start += end + 1;
        i++;
    }
    split = ft_strdup(line + start);
    if (!split)
    {
        // Gérer l'erreur.
        // Libérer la mémoire allouée jusqu'à présent avant de retourner NULL.
        while (i > 0) free(struct_cmds[--i].cmd);
        	free(struct_cmds);
        return NULL;
    }
    cleaned_split = rmv_spaces_quotes(split);
    	free(split);
    if (!cleaned_split)
    {
        // Gérer l'erreur.
        while (i > 0) free(struct_cmds[--i].cmd);
        	free(struct_cmds);
        return NULL;
    }
    struct_cmds[i].cmd = cleaned_split; 
    struct_cmds[i + 1].cmd = NULL;

    return (struct_cmds);
}
/*
		struct_cmds[i].cmd = ft_strndup(line + start, end);
		if (!struct_cmds[i].cmd)
			// gerer l'erreur
			return (NULL);
		start += end + 1;
		i++;
	}
	struct_cmds[i].cmd = ft_strdup(line + start);
	struct_cmds[i + 1].cmd = NULL;
	return (struct_cmds);
}*/

