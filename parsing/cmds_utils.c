/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:48:10 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/31 20:49:02 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	fcn_cont(t_cvr *cvr, char *str)
{
	if (str[cvr->i] == '|' && !cvr->qutrg)
	{
		cvr->j++;
		cvr->k = 0;
	}
	if ((str[cvr->i] == ' ' || str[cvr->i] == '|') \
	&& !cvr->qutrg && cvr->ctrg)
		cvr->ctrg = FALSE;
	if (str[cvr->i] != ' ' && str[cvr->i] != '|' && !cvr->ctrg)
	{
		cvr->cnum[cvr->j] = ++cvr->k;
		cvr->ctrg = TRUE;
	}
}

void	count_qut_pipe(t_cvr *cvr, char *str)
{
	if ((str[cvr->i] == '"' || str[cvr->i] == '\'') && !cvr->qutrg)
	{
		cvr->quchr = str[cvr->i];
		cvr->qutrg = TRUE;
	}
	else if ((str[cvr->i] == cvr->quchr) && cvr->qutrg)
	{
		cvr->quchr = '\0';
		cvr->qutrg = FALSE;
	}
	if (str[cvr->i] == '|' && !cvr->qutrg)
	{
		cvr->j++;
		cvr->k = 0;
		cvr->chars_num = 0;
	}
}

void	check_qut_pipe(t_cvr *cvr, char *str)
{
	if ((str[cvr->i] == '"' || str[cvr->i] == '\'') && !cvr->qutrg)
	{
		cvr->quchr = str[cvr->i];
		cvr->qutrg = TRUE;
	}
	else if ((str[cvr->i] == cvr->quchr) && cvr->qutrg)
	{
		cvr->quchr = '\0';
		cvr->qutrg = FALSE;
	}
	if (str[cvr->i] == '|' && !cvr->qutrg)
	{
		if (cvr->cmds[cvr->j][cvr->k])
			cvr->cmds[cvr->j][++cvr->k] = NULL;
		else
			cvr->cmds[cvr->j][cvr->k] = NULL;
		cvr->cmds[cvr->j][cvr->k] = NULL;
		cvr->k = 0;
		cvr->l = 0;
		cvr->j++;
	}
}

void	malloc_cmds(t_cvr *cvr)
{
	cvr->cmds = ft_calloc(cvr->parts_num + 1, sizeof(char **));
	if (!cvr->cmds)
		return ;
	cvr->i = -1;
	while (++cvr->i < cvr->parts_num)
	{
		cvr->cmds[cvr->i] = ft_calloc(cvr->cnum[cvr->i] + 1, sizeof(char *));
		if (!cvr->cmds[cvr->i])
			return ;
		cvr->j = -1;
		while (++cvr->j < cvr->cnum[cvr->i])
		{
			cvr->cmds[cvr->i][cvr->j] = \
			ft_calloc(cvr->chrn[cvr->i][cvr->j] + 1, sizeof(char));
			if (!cvr->cmds[cvr->i][cvr->j])
				return ;
		}
	}
	free (cvr->cnum);
	cvr->i = -1;
	cvr->j = 0;
}

void	init_cvr(t_cvr *cvr, char *str, int mode)
{
	cvr->i = -1;
	cvr->j = 0;
	cvr->k = 0;
	cvr->l = 0;
	cvr->chars_num = 0;
	cvr->len = ft_strlen(str);
	cvr->qutrg = FALSE;
	cvr->ctrg = FALSE;
	cvr->quchr = '\0';
	cvr->parts_num = find_parts_num(str);
	if (mode == 1 || mode == 2)
		cvr->cnum = find_cmds_num(str);
	if (mode == 2)
		cvr->chrn = find_cmds_chars_num(str);
}
