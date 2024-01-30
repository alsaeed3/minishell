/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tabs_to_spc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:38:22 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/31 00:46:49 by alsaeed          ###   ########.fr       */
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
	t_var	var;

	init_contabvar(&var, str);
	var.ret = malloc(sizeof(char *) * (var.len + 1));
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
	if (var.ret[var.j])
		var.ret[var.j] = '\0';
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