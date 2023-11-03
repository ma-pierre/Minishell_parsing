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
	while(is_alpha(str[i]) || is_digit(str[i]))
		i++;
	var = malloc(sizeof(char) * (i - count) + 1);
	if (!var)
		return(NULL);                 
	while (count < i)
		var[j++] = str[count++];
	var[j] = '\0';
	return (var);
}

/*char *build_expended_line(char *before, char *value, char *after) {
    if (value == NULL) {
        value = "";
    }

    // Calculez la taille totale nécessaire pour la nouvelle chaîne.
    int total_length = ft_strlen(before) + ft_strlen(value) + ft_strlen(after);

    // Allouez de la mémoire pour la nouvelle chaîne.
    char *expanded = malloc(sizeof(char) * (total_length + 1)); // +1 pour le caractère nul
    if (!expanded) {
        return NULL;
    }
	expanded[0] = '\0';
    // Initialisez la chaîne avec la partie "before".
    ft_strlcat(expanded, before, total_length + 1);

    // Ajoutez la valeur de la variable d'environnement.
    ft_strlcat(expanded, value, total_length + 1);

    // Ajoutez la partie "after".
    ft_strlcat(expanded, after, total_length + 1);

    return expanded;
}*/
char *build_expended_line(char *before, char *value, char *after)
{
	int i;
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

/*char *split_env(char *str)
{
	int dollar_pos;
	char *before;
	char *to_expand;
	char *after;
	char *expanded;
	char	*result;

	while (1)
	{
	dollar_pos = find_pos_dollar(str);
	if (dollar_pos == -1)
		break;
	before = ft_strndup(str, dollar_pos);
	to_expand = find_var_name(str, dollar_pos+1);
	after = ft_strndup(&str[dollar_pos + 1 + ft_strlen(to_expand)],
			ft_strlen(str));
	if (str[dollar_pos + 1] == '?')
		expanded = build_expended_line(before, to_expand, after);
	else
		expanded = build_expended_line(before, getenv(to_expand), after);
	printf("%s|\n", expanded);
	result = split_env(expanded);
	free(before);
        free(to_expand);
        free(after);
	}
	return (result);
}*/
char *split_env(char *str)
{
    char *result = str;
    int dollar_pos;
	char *expanded;

    while (1)
    {
        dollar_pos = find_pos_dollar(result);
        if (dollar_pos == -1)
            break;
        char *before = ft_strndup(result, dollar_pos);
		printf("_______BEFORE______%s\n", before);
        char *to_expand = find_var_name(result, dollar_pos + 1);
		printf("______TO EXPAND____%s\n", to_expand);
        char *after = ft_strndup(&result[dollar_pos + 1 + ft_strlen(to_expand)], ft_strlen(result));
		printf("________AFTER_____%s\n", after);
		printf("GET_ENV_RESULT =========== %s\n", getenv(to_expand));
        if (result[dollar_pos + 1] == '?')
            expanded = build_expended_line(before, to_expand, after);
        else
            expanded = build_expended_line(before, getenv(to_expand), after);
        printf("%s|\n", expanded);
        free(result);
        result = expanded;
        free(before);
        free(to_expand);
        free(after);
    }
    return result;
}
	
	
