/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:06:47 by habu-zua          #+#    #+#             */
/*   Updated: 2023/12/17 13:48:42 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int		nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			nbr++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (nbr);
}

static void	ft_free(char **rtn, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(rtn[j]);
	free(rtn);
}

static void	ft_fillwords(char **rtn, const char *s, char c, int nbr_w)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		j = 0;
		while (s[j] != c && s[j])
			j++;
		if (i < nbr_w)
		{
			rtn[i] = ft_substr(s, 0, j);
			if (!rtn[i])
				ft_free(rtn, i);
			i++;
		}
		s += j;
	}
	rtn[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**rtn;
	int		nbr_w;

	nbr_w = ft_word_count(s, c);
	rtn = malloc(sizeof(char *) * (nbr_w + 1));
	if (!rtn)
		return (0);
	ft_fillwords(rtn, s, c, nbr_w);
	if (!rtn)
		return (NULL);
	return (rtn);
}
