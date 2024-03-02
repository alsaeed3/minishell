/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tabs_to_spc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:38:22 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/09 15:54:12 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	*conv_tabs2spcs(char *cmd_line)
{
	int		i;
	int		j;
	char	trigger;
	int		len;
	char	*ret;

	trigger = -1;
	i		= -1;
	j		= -1;
	len = ft_strlen(cmd_line);
	ret = malloc(sizeof(char *) * (len + 1));
	while (++i < len)
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
		{
			ret[++j] = cmd_line[i];
			trigger = cmd_line[i];
			while (++i < len)
			{
				if (cmd_line[i] == trigger)
				{
					ret[++j] = cmd_line[i];
					break;
				}
				ret[++j] = cmd_line[i];
			}
		}
		else if (cmd_line[i] == '\t')
		{
			ret[++j] = ' ';
			while (cmd_line[i + 1] == '\t')
				i++;
		}
		else 
			ret[++j] = cmd_line[i];
	}
	ret[++j] = '\0';
	return(ret);
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
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:38:22 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/18 14:51:29 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

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

	var = (t_var){0};
	init_contabvar(&var, str);
	var.ret = ft_calloc(var.len + 1, sizeof(char));
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
	free_set_null((void **)&str);
	return (var.ret);
}

void	if_else_conv(t_var *var, char *str)
{
	if (var->rdrtrg)
	{
		if ((str[var->i] == ' ' || str[var->i] == '<' \
		|| str[var->i] == '>' || str[var->i] == '|' \
		|| str[var->i] == '\0') && !var->qutrg)
			var->rdrtrg = FALSE;
		var->nordr[var->j++] = ' ';
	}
	else
		var->nordr[var->j++] = str[var->i];
}
>>>>>>> main
