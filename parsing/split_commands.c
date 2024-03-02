/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:23:50 by alsaeed           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/07 16:47:16 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
=======
/*   Updated: 2024/02/19 16:22:54 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"
>>>>>>> main

int	*find_cmds_num(char *str)
{
	t_cvr	cvr;

	cvr = (t_cvr){0};
	init_cvr(&cvr, str, 0);
	cvr.cnum = ft_calloc(find_parts_num(str), sizeof(int));
	if (!cvr.cnum)
		return (NULL);
	while (++cvr.i < cvr.len)
	{
<<<<<<< HEAD
=======
		if (((str[cvr.i] == '"' && str[cvr.i + 1] == '"') \
		|| (str[cvr.i] == '\'' && str[cvr.i + 1] == '\'')) && !cvr.qutrg)
		{
			cvr.i++;
			continue ;
		}
>>>>>>> main
		if ((str[cvr.i] == '"' || str[cvr.i] == '\'') && !cvr.qutrg)
		{
			cvr.quchr = str[cvr.i];
			cvr.qutrg = TRUE;
		}
		else if ((str[cvr.i] == cvr.quchr) && cvr.qutrg)
			cvr.qutrg = FALSE;
		fcn_cont(&cvr, str);
	}
	return (cvr.cnum);
}

int	**find_cmds_chars_num(char *str)
{
	t_cvr	cvr;

	init_cvr(&cvr, str, 1);
	cvr.chrn = ft_calloc(cvr.parts_num, sizeof(int *));
	cvr.i = -1;
	while (++cvr.i < cvr.parts_num)
		cvr.chrn[cvr.i] = ft_calloc(cvr.cnum[cvr.i], sizeof(int));
	cvr.i = -1;
	while (++cvr.i < cvr.len && str[cvr.i])
	{
<<<<<<< HEAD
		count_qut_pipe(&cvr, str);
		if (str[cvr.i] == ' ' && (cvr.i == 0 || str[cvr.i - 1] != ' ') \
		&& (cvr.i == 0 || str[cvr.i - 1] != '|') && !cvr.qutrg)
		{
			cvr.k++;
			cvr.chars_num = 0;
		}
=======
		if (cnsqut_cmd_num(&cvr, str))
			continue ;
>>>>>>> main
		if (((str[cvr.i] != '|' && str[cvr.i] != '"' && str[cvr.i] != '\'' \
		&& str[cvr.i] != ' ' && str[cvr.i] != '\0') || ((str[cvr.i] != ' ' \
		|| str[cvr.i] == '|' || str[cvr.i] != '"' || str[cvr.i] != '\'') \
		&& (str[cvr.i] != cvr.quchr) && cvr.qutrg)))
			cvr.chrn[cvr.j][cvr.k] = ++cvr.chars_num;
	}
<<<<<<< HEAD
	free_set_null(cvr.cnum);
=======
	free_set_null((void **)&cvr.cnum);
>>>>>>> main
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
	if (str[cvr->i] == ' ' && (cvr->i == 0 || str[cvr->i - 1] != ' ') \
	&& (cvr->i == 0 || str[cvr->i - 1] != '|') && !cvr->qutrg && cvr->ctrg)
	{
		cvr->cmds[cvr->j][cvr->k++][cvr->l] = '\0';
		cvr->ctrg = FALSE;
	}
}

char	***split_cmds(char *str)
{
	t_cvr	cvr;

	cvr = (t_cvr){0};
	init_cvr(&cvr, str, 2);
	malloc_cmds(&cvr);
<<<<<<< HEAD
	ft_free_intarr(cvr.chrn, cvr.parts_num);
	while (++cvr.i < cvr.len)
	{
		check_qut_pipe(&cvr, str);
=======
	ft_free_intarr(&cvr.chrn, cvr.parts_num);
	while (++cvr.i < cvr.len)
	{
		if (cons_quot_cmd(&cvr, str))
			continue ;
>>>>>>> main
		if (str[cvr.i] == ' ' && (cvr.i == 0 || str[cvr.i - 1] != '|') \
		&& !cvr.qutrg)
		{
			cvr.k++;
			cvr.l = 0;
			cvr.ctrg = FALSE;
		}
		check_end_cmd(&cvr, str);
	}
	if (cvr.cmds[cvr.j])
		cvr.cmds[++cvr.j] = NULL;
	if (cvr.cnum)
<<<<<<< HEAD
		free_set_null(cvr.cnum);
	free_set_null(str);
=======
		free_set_null((void **)&cvr.cnum);
	free_set_null((void **)&str);
>>>>>>> main
	return (cvr.cmds);
}
