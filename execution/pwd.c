/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:27:07 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/16 20:49:00 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/exec.h"

void	handle_pwd(t_parse *data)
{
	printf("handle_pwd\n");
	ft_putstr(data->pwd);
	ft_putstr("\n");
	// g_status = 0;
}
