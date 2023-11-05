/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:28:19 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/05 17:45:43 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"

int	find_pos_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*find_var_name(char *str, int i)
{
	char	*var;
	int		count;
	int		j;

	j = 0;
	count = i;
	if (str[i] == '?')
		return (dollar_qm());
	while (is_digit(str[i]))
		i++;
	if (i == count)
	{
		while (is_alpha(str[i]) || is_digit(str[i]) || str[i] == '_')
			i++;
	}
	var = malloc(sizeof(char) * (i - count) + 1);
	if (!var)
		return (NULL);
	while (count < i)
		var[j++] = str[count++];
	var[j] = '\0';
	return (var);
}

char	*build_expanded_line(char *before, char *value, char *after)
{
	int		i;
	char	*expanded;

	if (value == NULL)
		value = "";
	i = (ft_strlen(before) + ft_strlen(value) + ft_strlen(after));
	expanded = malloc(sizeof(char) * (i + 1));
	if (!expanded)
		return (NULL);
	expanded[0] = '\0';
	ft_strlcat(expanded, before, ft_strlen(before) + 1);
	ft_strlcat(expanded, value, ft_strlen(before) + ft_strlen(value) + 1);
	ft_strlcat(expanded, after, i + 1);
	return (expanded);
}
char	*split_env(char *str, int dollar_pos)
{
	char	*before;
	char	*to_expand;
	char	*after;
	char	*expanded;

	before = ft_strndup(str, dollar_pos);
	to_expand = find_var_name(str, dollar_pos + 1);
	after = ft_strndup(&str[dollar_pos + 1 + ft_strlen(to_expand)],
		ft_strlen(str));
	if (str[dollar_pos + 1] == '?')
		expanded = build_expanded_line(before, to_expand, after);
	else
		expanded = build_expanded_line(before, getenv(to_expand), after);
	free(before);
	free(to_expand);
	free(after);
	return (expanded);
}

char	*expand_all(char *str)
{
	char	*result;
	int		dollar_pos;
	char	*temp;

	result = str;
	dollar_pos = find_pos_dollar(result);
	while (dollar_pos != -1)
	{
		temp = result;
		result = split_env(result, dollar_pos);
		free(temp);
		dollar_pos = find_pos_dollar(result);
	}
	return (result);
}
