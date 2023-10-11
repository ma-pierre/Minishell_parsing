#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAGENTA "\033[95m"
#define RESET   "\033[0m"

char	*check_quotes(char *str);
int		syntax_parse(char *str);
int		syntax_error(char c);
int		is_digit(int c);
int		is_alpha(int c);
int		is_redirection(int c);
int		is_operator(char c);
int		is_space(char c);
int		operator_parse(char *str, char op);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);