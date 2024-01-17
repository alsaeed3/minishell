/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:56:10 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/17 13:12:20 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parser.h"
# include "../inc/exec.h"

void	data_init(t_parse *data)
{
	data->pwd = getcwd(NULL, 0);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
}