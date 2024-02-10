/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dlr_sgn2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:10:29 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/10 17:02:59 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

char *ft_strstr(char *haystack,char *needle)
{
    size_t len;

    len = ft_strlen(needle);
    if (!*needle)
        return (haystack);
    while (*haystack)
    {
        if (!ft_strncmp(haystack, needle, len))
            return (haystack);
        haystack++;
    }
    return (NULL);
}
char *ft_strncpy(char *dest, char *src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}
char *ft_strcpy(char *dest, char *src)
{
    size_t i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

// char *ft_strreplace(char *orig, char *rep, char *with) {
// 	char *result; // the return string
// 	char *ins;    // the next insert point
// 	char *tmp;    // varies
// 	int len_rep;  // length of rep (the string to remove)
// 	int len_with; // length of with (the string to replace rep with)
// 	int len_front; // distance between rep and end of last rep
// 	int count;    // number of replacements

// 	if (!orig || !rep)
// 		return NULL;
// 	len_rep = ft_strlen(rep);
// 	if (len_rep == 0)
// 		return NULL; // empty rep causes infinite loop during count
// 	if (!with)
// 		with = "";
// 	len_with = ft_strlen(with);
// 	ins = orig;
// 	for (count = 0; (tmp = ft_strstr(ins, rep)); ++count) {
// 		ins = tmp + len_rep;
// 	}
// 	result = malloc(ft_strlen(orig) + (len_with - len_rep) * count + 1);
// 	tmp = result;
// 	if (!result)
// 		return NULL;
// 	while (count--) {
// 		ins = ft_strstr(orig, rep);
// 		len_front = ins - orig;
// 		tmp = ft_strncpy(tmp, orig, len_front) + len_front;
// 		tmp = ft_strcpy(tmp, with) + len_with;
// 		orig += len_front + len_rep; // move to next "end of rep"
// 	}
// 	ft_strcpy(tmp, orig);
// 	return result;
// }

static int count_replacements(char *orig, char *rep)
{
    int count;
    char *ins;

    count = 0;
    ins = orig;
    ins = ft_strstr(ins, rep);
    while (ins != NULL)
    {
        count++;
        ins += ft_strlen(rep); // move to the next potential match
        ins = ft_strstr(ins, rep);
    }
    return count;
}

static void perform_replacements(char *result, char *orig, char *rep, char *with)
{
    char *tmp = result;
    char *ins = orig;
    size_t len_rep;
    size_t len_front;
    size_t len_with;
    
    len_rep = ft_strlen(rep);
    len_with = ft_strlen(with);
    ins = ft_strstr(ins, rep);
    while (ins != NULL) {
        len_front = ins - orig;
        tmp = ft_strncpy(tmp, orig, len_front) + len_front;
        tmp = ft_strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
        ins += len_rep; // move to the next potential match
        ins = ft_strstr(ins, rep);
    }
    ft_strcpy(tmp, orig);
}

char *ft_strreplace(char *orig, char *rep, char *with)
{
    if (!orig || !rep) {
        return NULL;
    }
    size_t len_rep;
    len_rep= ft_strlen(rep);
    if (len_rep == 0) {
        return NULL; // empty rep causes infinite loop during count
    }
    if (!with) {
        with = "";
    }
    size_t len_orig;
    len_orig= ft_strlen(orig);
    int count = count_replacements(orig, rep);
    char *result = malloc(len_orig + (ft_strlen(with) - len_rep) * count + 1);
    if (!result) {
        return NULL;
    }
    perform_replacements(result, orig, rep, with);
    return result;
}

void inside_loop(char **input, char *c, t_parse *data)
{
    char *tmp;

    tmp = NULL;
    if (*c == '?')
    {
        tmp = ft_itoa(data->exit_status);
        *input = ft_strreplace(*input, "$?", tmp);
        free_set_null(tmp);
    }
    else if (*c == '0')
        *input = ft_strreplace(*input, "$0", "minishell");
    else if (ft_isalpha(*c) || ft_isdigit(*c) || *c == '_' || *c == '*')
    {
        tmp = ft_strjoin("$", c);
        *input = ft_strreplace(*input, tmp,"");
        free_set_null(tmp);
    }
}
void expand_dolar_sign(char **inputs, t_parse *data)
{
	int	i;
	int	j;
    // int len;
    char c;

	i = 0;
	while (inputs[i])
	{
        // len = ft_strlen(inputs[i]);
		j = 0;
		while (inputs[i][j])
		{
			if (/* j < len - 1 && */ inputs[i][j] == '$')
			{
                c = inputs[i][j + 1];
                inside_loop(&inputs[i], &c, data);
				j++;
			}
			j++;
		}
		i++;
	}
}
