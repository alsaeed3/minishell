/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:56:10 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/03 17:07:11 by habu-zua         ###   ########.fr       */
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
	(*data)->tot_inredir = 0;
	(*data)->tot_outredir = 0;
	(*data)->heredocs_num = 0;
	(*data)->fd_in = 0;
	(*data)->fd_out = 1;
	(*data)->redir = 1;
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
	(*data)->redir = 1;

	return (FALSE);
}