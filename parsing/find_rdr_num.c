/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rdr_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:47:49 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/30 22:54:32 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_bool	init_rdr_vars(t_var *var, t_parse *data, char *str, char rdr)
{
	var->i = -1;
	var->j = 0;
	var->k = 0;
	var->l = -1;
	var->len = ft_strlen(str);
	var->parts_num = find_parts_num(str);
	var->qutrg = FALSE;
	var->qchr = '\0';
	var->rdrtrg = FALSE;
	var->rnum = NULL;
	var->rcn = NULL;
	if (rdr == '<' && data->tot_inredir)
		var->rnum = data->in_rdr_num;
	else if (rdr == '>' && data->tot_outredir)
		var->rnum = data->out_rdr_num;
	if (rdr == '<' && !data->tot_inredir)
		return (TRUE);
	else if (rdr == '>' && !data->tot_outredir)
		return (TRUE);
	return (FALSE);
}

void	find_tot_rdr(char rdr, t_parse *data)
{
	if (rdr == '<')
		data->tot_inredir++;
	else if (rdr == '>')
		data->tot_outredir++;
}

int	ret_rnum(char rdr, t_parse *data)
{
	if (rdr == '<')
		return (data->tot_inredir);
	else if (rdr == '>')
		return (data->tot_outredir);
	return (0);
}

void	quote_context(char *str, t_var *var)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qchr = str[var->i];
		var->qutrg = TRUE;
	}
	else if ((str[var->i] == var->qchr) && var->qutrg)
	{
		var->qchr = '\0';
		var->qutrg = FALSE;
	}
}

int	*find_rdr_num(char *str, char rdr, t_parse *data)
{
	t_var	var;

	init_rdr_vars(&var, data, str, rdr);
	var.rnum = ft_calloc(var.parts_num, sizeof(int));
	while (++var.i < var.len)
	{
		quote_context(str, &var);
		if (str[var.i] == '|' && !var.qutrg && var.j < var.parts_num)
			var.j++;
		if (var.i < var.len - 1 && (str[var.i] == rdr && str[var.i + 1] != rdr \
			&& (var.i == 0 || str[var.i - 1] != rdr)) && !var.qutrg)
			find_tot_rdr(rdr, data);
		else if (var.i < var.len - 1 && (str[var.i] == rdr \
			&& str[var.i + 1] == rdr) && !var.qutrg)
			find_tot_rdr(rdr, data);
		var.rnum[var.j] = ret_rnum(rdr, data);
	}
	return (var.rnum);
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