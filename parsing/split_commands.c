/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:23:50 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/30 22:29:48 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	*find_cmds_num(char *str)
{
	t_cvr	cvr;

	init_cvr(&cvr, str);
	cvr.cnum = ft_calloc(find_parts_num(str), sizeof(int));
	while (++cvr.i < cvr.len)
	{
		if ((str[cvr.i] == '"' || str[cvr.i] == '\'') && !cvr.qutrg)
		{
			cvr.quchr = str[cvr.i];
			cvr.qutrg = TRUE;
		}
		else if ((str[cvr.i] == cvr.quchr) && cvr.qutrg)
			cvr.qutrg = false;
		fcn_cont(&cvr, str);
	}
	return (cvr.cnum);
}

int	**find_cmds_chars_num(char *str)
{
	t_cvr	cvr;

	init_cvr(&cvr, str);
	cvr.chrn = ft_calloc(cvr.parts_num, sizeof(int *));
	while (++cvr.i < cvr.parts_num)
		cvr.chrn[cvr.i] = ft_calloc(cvr.cnum[cvr.i], sizeof(int));
	cvr.i = -1;
	while (++cvr.i < cvr.len && str[cvr.i])
	{
		count_qut_pipe(&cvr, str);
		if (str[cvr.i] == ' ' && (cvr.i == 0 || str[cvr.i - 1] != ' ') \
		&& (cvr.i == 0 || str[cvr.i - 1] != '|') && !cvr.qutrg)
		{
			cvr.k++;
			cvr.chars_num = 0;
		}
		if (((str[cvr.i] != '|' && str[cvr.i] != '"' && str[cvr.i] != '\'' \
		&& str[cvr.i] != ' ' && str[cvr.i] != '\0') || ((str[cvr.i] != ' ' \
		|| str[cvr.i] == '|' || str[cvr.i] != '"' || str[cvr.i] != '\'') \
		&& (str[cvr.i] != cvr.quchr) && cvr.qutrg)))
			cvr.chrn[cvr.j][cvr.k] = ++cvr.chars_num;
	}
	return (cvr.chrn);
}

void	check_end_cmd(t_cvr *cvr, char *str)
{
	if ((str[cvr->i] != ' ' && str[cvr->i] != '|' && str[cvr->i] != '\'' \
	&& str[cvr->i] != '"') || ((str[cvr->i] == ' ' || str[cvr->i] == '|' \
	|| str[cvr->i] == '\'' || str[cvr->i] == '"') \
	&& (str[cvr->i] != cvr->quchr) && cvr->qutrg))
	{
		cvr->cmds[cvr->j][cvr->k][cvr->l++] = str[cvr->i];
		if ((str[cvr->i + 1] == ' ' || str[cvr->i + 1] == '|') \
		&& !cvr->qutrg)
			cvr->cmds[cvr->j][cvr->k][cvr->l] = '\0';
	}
}

char	***split_cmds(char *str)
{
	t_cvr	cvr;

	init_cvr(&cvr, str);
	malloc_cmds(&cvr);
	while (++cvr.i < cvr.len)
	{
		check_qut_pipe(&cvr, str);
		if (str[cvr.i] == ' ' && (cvr.i == 0 || str[cvr.i - 1] != '|') \
		&& !cvr.qutrg)
		{
			cvr.k++;
			cvr.l = 0;
			cvr.ctrg = FALSE;
		}
		check_end_cmd(&cvr, str);
		if (str[cvr.i] == ' ' && (cvr.i == 0 || str[cvr.i - 1] != ' ') \
		&& (cvr.i == 0 || str[cvr.i - 1] != '|') && !cvr.qutrg && cvr.ctrg)
		{
			cvr.cmds[cvr.j][cvr.k++][cvr.l] = '\0';
			cvr.ctrg = FALSE;
		}
	}
	if (cvr.cmds[cvr.j])
		cvr.cmds[++cvr.j] = NULL;
	return (cvr.cmds);
}
