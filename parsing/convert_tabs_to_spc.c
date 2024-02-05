/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tabs_to_spc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:38:22 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/05 21:12:57 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_contabvar(t_var *var, char *str)
{
	var->i = -1;
	var->j = 0;
	var->len = ft_strlen(str);
	var->ret = NULL;
	var->qutrg = FALSE;
	var->qchr = '\0';
}

char	*conv_tabs2spcs(char *str)
{
	t_var	var = {0};

	init_contabvar(&var, str);
	var.ret = ft_calloc(var.len + 1, sizeof(char *));
	if (!var.ret)
		return (NULL);
	while (++var.i < var.len)
	{
		if ((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.qchr = str[var.i];
			var.qutrg = TRUE;
		}
		else if (str[var.i] == var.qchr && var.qutrg)
		{
			var.qchr = '\0';
			var.qutrg = FALSE;
		}
		if (str[var.i] == '\t' && !var.qutrg)
			str[var.i] = ' ';
		var.ret[var.j++] = str[var.i];
	}
	var.ret[var.j] = '\0';
	free (str);
	str = NULL;
	return (var.ret);
}

// int main(void)
// {
// 	char *str;
// 	char *hell;

// 	while (1)
// 	{
// 		str = readline("> ");
// 		hell = conv_tabs2spcs(str);
// 		free(str);
// 		printf("%s\n", hell);
// 		free(hell);
// 	}
// 	return (0);
// }