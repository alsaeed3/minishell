/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:56:10 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/20 17:14:34 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/exec.h"

void	data_init(t_parse **data, char **env)
{
	*data = ft_calloc(1, sizeof(t_parse));
	if (!(*data))
		return ;
	(*data)->env = dup_env(env);
	(*data)->pwd = getcwd(NULL, 0);
	(*data)->fd_in = 0;
	(*data)->fd_out = 1;
	(*data)->redir = 1;
}