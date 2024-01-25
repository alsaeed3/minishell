/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rdr_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:47:49 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/25 21:42:20 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_rdr_vars(t_var *var, char *str, int mode, char rdr)
{
	printf("find_rdr_num %c\n", rdr);
	var->i = -1;
	var->j = 0;
	var->k = -1;
	var->l = -1;
	var->len = ft_strlen(str);
	var->parts_num = find_parts_num(str);
	var->rdrtrg = FALSE;
	var->qutrg = FALSE;
	var->quchr = '\0';
	var->chrnum = 0;
	if (mode == 2)
	{
		var->rdrnum = find_rdr_num(str, rdr);
		var->rcn = ft_calloc(var->parts_num, sizeof(int *));
		var->i = -1;
		while (++var->i < var->parts_num)
			var->rcn[var->i] = ft_calloc(var->rdrnum[var->i], sizeof(int));
		var->i = -1;
	}
	else if (mode == 3)
	{
		var->rdrnum = find_rdr_num(str, rdr);
		var->rcn = find_rdr_chars(str, rdr);
		var->rdrnms = malloc_rdr_names(var->parts_num, var->rdrnum, var->rcn);
	}
}

int	*find_rdr_num(char *str, char rdr)
{
	printf("find_rdr_num %c\n", rdr);
	t_var	var;

	init_rdr_vars(&var, str, 1, rdr);
	while (++var.i < var.len)
	{
		if ((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.quchr = str[var.i];
			var.qutrg = TRUE;
		}
		else if ((str[var.i] == var.quchr) && var.qutrg)
		{
			var.quchr = '\0';
			var.qutrg = FALSE;
		}
		if (str[var.i] == '|' && !var.qutrg && var.j < var.parts_num)
			var.j++;
		if (var.i < var.len - 1 && (str[var.i] == rdr && str[var.i + 1] != rdr \
			&& (var.i == 0 || str[var.i - 1] != rdr)) && !var.qutrg)
			var.rdrnum[var.j]++;
		else if (var.i < var.len - 1 && (str[var.i] == rdr \
			&& str[var.i + 1] == rdr) && !var.qutrg)
			var.rdrnum[var.j]++;
	}
	return (var.rdrnum);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		int *infiles_heredocs_num;
// 		char *input = readline("$> ");
// 		int parts_num = find_parts_num(input);
// 		infiles_heredocs_num = find_infiles_heredocs_num(input, parts_num);
// 		free (input);
// 		int i = -1;
// 		while (++i < (parts_num))
// 			printf("part %d: %d\n", i, infiles_heredocs_num[i]);
// 		free (infiles_heredocs_num);
// 	}
// }