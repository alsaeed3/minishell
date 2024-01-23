/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:56:10 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/23 13:49:44 by alsaeed          ###   ########.fr       */
=======
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:56:10 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/20 11:11:03 by habu-zua         ###   ########.fr       */
>>>>>>> 327bff9243871fd0844917392bed6222de3a4986
/*                                                                            */
/* ************************************************************************** */

# include "../inc/exec.h"

void	data_init(t_parse *data, char **env)
{
<<<<<<< HEAD
	(*data)->env = dup_env(env);
	(*data)->pwd = getcwd(NULL, 0);
	(*data)->envs_lst = NULL;
	(*data)->tot_inredir = 0;
	(*data)->tot_outredir = 0;
	(*data)->heredocs_num = 0;
	(*data)->fd_in = 0;
	(*data)->fd_out = 1;
	(*data)->redir = 1;
=======
	data->env = dup_env(env);
	data->pwd = getcwd(NULL, 0);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
>>>>>>> 327bff9243871fd0844917392bed6222de3a4986
}