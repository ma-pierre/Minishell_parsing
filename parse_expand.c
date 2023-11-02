#include "minishell_parse.h"

int	find_pos_dollar(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*find_var_name(char *str, int i)
{
	char *var;
	int count;
	int	j;

	j = 0;
	count = i;
	if (str[i] == '?')
	{
		var = malloc(2);
		if(!var)
			return (NULL);
		var[j++] = '0' + DQM;
		var[j] = '\0';
		return (var);
		//dqm est un int defini dans le .h , a remplacer par lexit status recu par lexec
	}
	//rajouter que si le premier caractere apres $ est un digit alors cest faux;checker bash(tant que cest des numeros alors ca ne compte pas)
	while(is_alpha(str[i]) || is_digit(str[i]) || is_space(str[i]))
		i++;
	var = malloc(sizeof(char) * (i - count) + 1);
	if (!var)
		return(NULL);                 
	while (count < i)
		var[j++] = str[count++];
	var[j] = '\0';
	return (var);
}

char *build_expended_line(char *before, char *value, char *after)
{
	size_t i;
	char *expanded;

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

char *split_env(char *str)
{
	int dollar_pos;
	char *before;
	char *after;
	char *expanded;
	char *var_name;
	char *value;

	dollar_pos = find_pos_dollar(str);
	if (dollar_pos == -1)
		return (str);
	before = ft_strndup(str, dollar_pos);
	if (!before)
		return (NULL);
	var_name = find_var_name(str, dollar_pos + 1);
    if (!var_name)
	{
        free(before);
        return NULL;
    }
	if (strcmp(var_name, "?") == 0)
        value = ft_itoa(DQM);
	else
        value = getenv(var_name);
	after = ft_strdup(&str[dollar_pos + 1 + ft_strlen(var_name)]);
	 if (!after) 
	 {
        free(before);
        free(var_name);
        if (value != getenv(var_name))
            free(value);
        return NULL;
    }
	expanded = build_expended_line(before, value, after);
	free(before);
    free(var_name);
    free(after);
    if (value != getenv(var_name)){
        free(value);
	}
	if (expanded != str) {
        free(str);
	}
	printf("EXPAND ====== %s|\n", expanded);
	return (expanded);
}
	
	
