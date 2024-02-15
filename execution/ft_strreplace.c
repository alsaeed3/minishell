/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:41:46 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/15 16:38:10 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static int	count_replacements(char *orig, char *rep)
{
	int		count;
	char	*ins;

	count = 0;
	ins = orig;
	ins = ft_strstr(ins, rep);
	while (ins != NULL)
	{
		count++;
		ins += ft_strlen(rep);
		ins = ft_strstr(ins, rep);
	}
	return (count);
}

static void	perform_replacements(char *result, char *orig, \
char *rep, char *with)
{
	char	*tmp;
	char	*ins;
	size_t	len_rep;
	size_t	len_front;
	size_t	len_with;

	tmp = result;
	ins = orig;
	len_rep = ft_strlen(rep);
	len_with = ft_strlen(with);
	ins = ft_strstr(ins, rep);
	while (ins != NULL)
	{
		len_front = ins - orig;
		tmp = ft_strncpy(tmp, orig, len_front) + len_front;
		tmp = ft_strcpy(tmp, with) + len_with;
		orig += len_front + len_rep;
		ins += len_rep;
		ins = ft_strstr(ins, rep);
	}
	ft_strcpy(tmp, orig);
}

char	*ft_strreplace(char *orig, char *rep, char *with)
{
	size_t	len_rep;
	size_t	len_orig;
	int		count;
	char	*result;

	if (!orig || !rep)
		return (NULL);
	len_rep = ft_strlen(rep);
	if (len_rep == 0)
		return (NULL);
	if (!with)
		with = "";
	len_orig = ft_strlen(orig);
	count = count_replacements(orig, rep);
	result = malloc(len_orig + (ft_strlen(with) - len_rep) * count + 1);
	if (!result)
		return (NULL);
	perform_replacements(result, orig, rep, with);
	return (result);
}
