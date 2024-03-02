/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:56:10 by habu-zua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/13 13:57:41 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/21 16:35:13 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	get_shlvl(t_parse *data)
{
	int		shlvl;
	int		index;
	char	*tmp;
	char	*new;

	index = 0;
	shlvl = 0;
	if (getenv("SHLVL"))
		shlvl = ft_atoi(getenv("SHLVL"), NULL) + 1;
	else
		shlvl = 2;
	index = var_index("SHLVL", data);
	tmp = ft_itoa(shlvl);
	new = ft_strjoin("SHLVL=", tmp);
<<<<<<< HEAD
	free_set_null(tmp);
	replace_var(new, data, index);
	free_set_null(new);
=======
	free_set_null((void **)&tmp);
	replace_var(new, data, index);
	free_set_null((void **)&new);
>>>>>>> main
}

t_bool	data_init(t_parse **data, char **env)
{
	if (!(*data))
		return (TRUE);
	if (env)
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
	(*data)->fds = ft_calloc(1, sizeof(t_fd));
	if (!(*data)->fds)
		return (TRUE);
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

void	set_up_prompt(t_parse **data, char *cmd_line)
{
	if (g_signal == 99)
		(*data)->exit_status = 1;
<<<<<<< HEAD
	g_signal = 1;
	if (cmd_line == NULL)
	{
		ft_putendl_fd("exit", 2);
		// rl_clear_history();
=======
	if (cmd_line == NULL)
	{
		ft_putendl_fd("exit", 2);
>>>>>>> main
		free_util_1(data);
		exit(0);
	}
	add_history(cmd_line);
	if (g_signal == 99)
		(*data)->exit_status = 1;
}
