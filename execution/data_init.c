/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:56:10 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/09 16:30:47 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	get_shlvl(t_parse *data)
{
	int	shlvl;
	int	index;

	index = 0;
	shlvl = 0;
	shlvl = ft_atoi(getenv("SHLVL"), NULL) + 1;
	index = var_index("SHLVL", data);
	replace_var(ft_strjoin("SHLVL=", ft_itoa(shlvl)), data, index);
}

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
	get_shlvl(*data);
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

void	set_up_prompt(t_parse **parser, char *cmd_line)
{
	if (g_signal == 99)
		(*parser)->exit_status = 1;
	g_signal = 1;
	if (cmd_line == NULL)
	{
		ft_putendl_fd("exit", 2);
		// rl_clear_history();
		free_util_1(parser);
		exit(0);
	}
	add_history(cmd_line);
	if (g_signal == 99)
		(*parser)->exit_status = 1;
}
