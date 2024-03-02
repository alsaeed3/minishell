/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:22:53 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/26 18:45:54 by habu-zua         ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:22:53 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/12 21:08:34 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	close_fds(t_parse *data)
{
	if (data->fd_in != 0)
	{
		close(data->fd_in);
		data->fd_in = 0;
	}
<<<<<<< HEAD
	if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 1;
=======
	else if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 0;
>>>>>>> main
	}
}
