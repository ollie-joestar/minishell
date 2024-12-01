/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:46:04 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/01 17:31:25 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;

    if (new_size == 0)
        return (free(ptr), NULL);
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);
    if (ptr)
    {
        if (old_size > new_size)
            ft_memcpy(new_ptr, ptr, new_size);
        else
            ft_memcpy(new_ptr, ptr, old_size);
        free(ptr);
    }
    return (new_ptr);
}

char *get_env_value(t_data *data, char *var_name)
{
    t_envlist *current;

    if (!data || !var_name)
        return (NULL);
    current = data->env;
    while (current)
    {
        if (ft_strncmp(current->name, var_name, ft_strlen(var_name)) == 0)
			return (current->value);
        current = current->next;
    }
    return (NULL);
}

/*char *expand(t_data *data, char *word)*/
/*{*/
/*    char    *result = NULL;*/
/*    size_t  result_size = 0;*/
/*    size_t  old_result_size = 0;*/
/*    size_t  i = 0;*/
/*    size_t  j = 0;*/
/*    size_t  word_len = ft_strlen(word);*/
/*    char    var_name[256];*/
/*    char    *var_value;*/
/*    char    *exit_status_str;*/
/*    size_t  len;*/
/**/
/*    result_size = word_len + 1;*/
/*    result = ft_calloc(result_size, sizeof(char));*/
/*    if (!result)*/
/*        return NULL;*/
/*    while (word[i] != '\0')*/
/*    {*/
/*        if (word[i] == '$')*/
/*        {*/
/*            i++;*/
/*            if (word[i] == '\0')*/
/*            {*/
/*                if (j + 1 >= result_size)*/
/*                {*/
/*                    old_result_size = result_size;*/
/*                    result_size = j + 2;*/
/*                    result = ft_realloc(result, old_result_size, result_size);*/
/*                    if (!result)*/
/*                        return NULL;*/
/*                }*/
/*                result[j++] = '$';*/
/*            }*/
/*            else if (word[i] == '?')*/
/*            {*/
/*                exit_status_str = ft_itoa(data->exit_status);*/
/*                if (!exit_status_str)*/
/*                {*/
/*                    free(result);*/
/*                    return NULL;*/
/*                }*/
/*                len = ft_strlen(exit_status_str);*/
/*                if (j + len >= result_size)*/
/*                {*/
/*                    old_result_size = result_size;*/
/*                    result_size = j + len + 1;*/
/*                    result = ft_realloc(result, old_result_size, result_size);*/
/*                    if (!result)*/
/*                    {*/
/*                        free(exit_status_str);*/
/*                        return NULL;*/
/*                    }*/
/*                }*/
/*                ft_memcpy(&result[j], exit_status_str, len);*/
/*                j += len;*/
/*                free(exit_status_str);*/
/*                i++;*/
/*            }*/
/*            else if (ft_isalpha(word[i]) || word[i] == '_')*/
/*            {*/
/*                size_t var_len = 0;*/
/*                while (word[i] != '\0' && (ft_isalnum(word[i]) || word[i] == '_'))*/
/*                {*/
/*                    if (var_len < sizeof(var_name) - 1)*/
/*                        var_name[var_len++] = word[i];*/
/*                    i++;*/
/*                }*/
/*                var_name[var_len] = '\0';*/
/*                var_value = get_env_value(data, var_name);*/
/*                if (!var_value)*/
/*                    var_value = ""; // Undefined variables expand to empty string*/
/*                len = ft_strlen(var_value);*/
/*                if (j + len >= result_size)*/
/*                {*/
/*                    old_result_size = result_size;*/
/*                    result_size = j + len + 1;*/
/*                    result = ft_realloc(result, old_result_size, result_size);*/
/*                    if (!result)*/
/*                        return NULL;*/
/*                }*/
/*                ft_memcpy(&result[j], var_value, len);*/
/*                j += len;*/
/*            }*/
/*            else*/
/*            {*/
/*                if (j + 2 >= result_size)*/
/*                {*/
/*                    old_result_size = result_size;*/
/*                    result_size = j + 3;*/
/*                    result = ft_realloc(result, old_result_size, result_size);*/
/*                    if (!result)*/
/*                        return NULL;*/
/*                }*/
/*                result[j++] = '$';*/
/*                result[j++] = word[i++];*/
/*            }*/
/*        }*/
/*        else*/
/*        {*/
/*            if (j + 1 >= result_size)*/
/*            {*/
/*                old_result_size = result_size;*/
/*                result_size = j + 2;*/
/*                result = ft_realloc(result, old_result_size, result_size);*/
/*                if (!result)*/
/*                    return NULL;*/
/*            }*/
/*            result[j++] = word[i++];*/
/*        }*/
/*    }*/
/*    result[j] = '\0';*/
/*    return result;*/
/*}*/

int handle_dollar_expansion(t_data *data, char **result, size_t *j, size_t *result_size, size_t *old_result_size)
{
    char *exit_status_str = ft_itoa(data->exit_status);
    size_t len;

    exit_status_str = ft_itoa(data->exit_status);
    if (!exit_status_str)
    {
        free(*result);
        return (-1);
    }
    len = ft_strlen(exit_status_str);
    if (*j + len >= *result_size)
    {
        *old_result_size = *result_size;
        *result_size = *j + len + 1;
        *result = ft_realloc(*result, *old_result_size, *result_size);
        if (!*result)
        {
            free(exit_status_str);
            return (-1);
        }
    }
    ft_memcpy(&(*result)[*j], exit_status_str, len);
    *j += len;
    free(exit_status_str);
    return 0;
}

int handle_variable_expansion(char *word, size_t *i, t_data *data, char **result, size_t *j, size_t *result_size, size_t *old_result_size)
{
    char var_name[256];
    char *var_value;
    size_t len;
    size_t var_len = 0;

    while (word[*i] != '\0' && (ft_isalnum(word[*i]) || word[*i] == '_'))
    {
        if (var_len < sizeof(var_name) - 1)
            var_name[var_len++] = word[*i];
        (*i)++;
    }
    var_name[var_len] = '\0';
    var_value = get_env_value(data, var_name);
    if (!var_value)
        var_value = ""; // Undefined variables expand to empty string
    len = ft_strlen(var_value);
    if (*j + len >= *result_size)
    {
        *old_result_size = *result_size;
        *result_size = *j + len + 1;
        *result = ft_realloc(*result, *old_result_size, *result_size);
        if (!*result)
            return (-1);
    }
    ft_memcpy(&(*result)[*j], var_value, len);
    *j += len;
    return 0;
}

int handle_regular_character(char c, char **result, size_t *j, size_t *result_size, size_t *old_result_size)
{
    if (*j + 1 >= *result_size)
    {
        *old_result_size = *result_size;
        *result_size = *j + 2;
        *result = ft_realloc(*result, *old_result_size, *result_size);
        if (!*result)
            return (-1);
    }
    (*result)[(*j)++] = c;
    return 0;
}

char *expand(t_data *data, char *word)
{
    char    *result = NULL;
    size_t  result_size = 0;
    size_t  old_result_size = 0;
    size_t  i = 0;
    size_t  j = 0;
    size_t  word_len = ft_strlen(word);

    result_size = word_len + 1;
    result = ft_calloc(result_size, sizeof(char));
    if (!result)
        return NULL;
    while (word[i] != '\0')
    {
        if (word[i] == '$')
        {
            i++;
            if (word[i] == '\0')
            {
                if (handle_regular_character('$', &result, &j, &result_size, &old_result_size) == -1)
                    return NULL;
            }
            else if (word[i] == '?')
            {
                i++;
                if (handle_dollar_expansion(data, &result, &j, &result_size, &old_result_size) == -1)
                    return NULL;
            }
            else if (ft_isalpha(word[i]) || word[i] == '_')
            {
                if (handle_variable_expansion(word, &i, data, &result, &j, &result_size, &old_result_size) == -1)
                    return NULL;
            }
            else
            {
                if (handle_regular_character('$', &result, &j, &result_size, &old_result_size) == -1)
                    return NULL;
                if (handle_regular_character(word[i++], &result, &j, &result_size, &old_result_size) == -1)
                    return NULL;
            }
        }
        else
        {
            if (handle_regular_character(word[i++], &result, &j, &result_size, &old_result_size) == -1)
                return NULL;
        }
    }
    result[j] = '\0';
    return result;
}
