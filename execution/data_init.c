/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:56:10 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/05 17:31:54 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

t_bool	data_init(t_parse **data, char **env)
{
	if (!(*data))
		return (TRUE);
	(*data)->env = dup_env(env);
	(*data)->pwd = getcwd(NULL, 0);
	(*data)->envs_lst = NULL;
	(*data)->heredoc_tmp_files = NULL;
	(*data)->inputs_tokens = NULL;
	(*data)->outputs_tokens = NULL;
	(*data)->in_rdr_num = NULL;
	(*data)->out_rdr_num = NULL;
	(*data)->tot_inredir = 0;
	(*data)->tot_outredir = 0;
	(*data)->heredocs_num = 0;
	(*data)->fd_in = 0;
	(*data)->fd_out = 1;
	(*data)->h_index = -1;
	return (FALSE);
}

t_bool	data_reset(t_parse **data)
{
	if (!(*data))
		return (TRUE);
	(*data)->tot_inredir = 0;
	(*data)->tot_outredir = 0;
	(*data)->heredocs_num = 0;
	(*data)->fd_in = 0;
	(*data)->fd_out = 1;
	return (FALSE);
}