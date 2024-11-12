#include "minishell.h"
/*
void	cat_single_quotes(char *str, char **start, char *end, size_t len)
{
	*end = 0;
	ft_strlcat(str, (*start) + 1, len + 1);
	*end = '\'';
	*start = end;
}

void	cat_double_quotes(t_data *data, char *str, char **start, char *end)
{
	*end = 0;
	(*start)++;
	while (*start < end)
	{
		if (possible_var(var, start[0][0], start[0][1]))
			cat_env_var(var, str, start, end);
		else
			cat_char_to_str(str, **start, data->len);
		(*start)++;
	}
	*end = '\"';
}

void	cat_status(char *str, int status, size_t len)
{
	char	s[BUFFER_SIZE];
	int		i;
	int		digits;
	int		base;

	ft_bzero(s, BUFFER_SIZE);
	base = 10;
	i = base;
	digits = digits_count(status, base);
	if (status == 0)
		s[--i] = '0';
	while (status > 0)
	{
		s[--i] = status % base + '0';
		status /= base;
	}
	ft_strlcat(str, s + (base - digits), len + 1);
}

void	cat_env_var(t_data *data, char *str, char **start, char *end)
{
	size_t	i;
	size_t	tkn_i;
	char	tmp;

	i = 0;
	if (start[0][1] == '?')
	{
		(*start) += 1;
		cat_status(str, data->status, data->len);
	}
	else if (env_var_len(data, *start, end, &i))
	{
		(*start)++;
		tmp = start[0][i];
		start[0][i] = 0;
		tkn_i = ft_strlen(str);
		mark_whitespaces(str + tkn_i);
		start[0][i] = tmp;
		*start += i - 1;
	}
	else
		*start += i;
}

char	*cat_interpreted_str(t_data *data, char *start, char *end)
{
	char	*ptr;
	char	*str;

	str = ft_calloc(data->len + 1, sizeof (char));
	if (!str)
		return (NULL);
	while (start < end)
	{
		if (*start == '\'' && check_single_quotes(&start, &ptr))
			cat_single_quotes(str, &start, ptr, data->len);
		else if (*start == '\"' && check_double_quotes(&start, &ptr))
			cat_double_quotes(data, str, &start, ptr);
		else if (possible_var(data, start[0], start[1]))
			cat_env_var(data, str, &start, end);
		else if (!lone_dollar_sign(start, end))
			cat_char_to_str(str, *start, data->len);
		start++;
	}
	return (str);
}*/
