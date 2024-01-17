/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:45:20 by alsaeed           #+#    #+#             */
/*   Updated: 2023/10/12 13:54:39 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_front(t_list *head, int integer)
{
	t_list	*new_node;

	if (head != NULL)
	{
		new_node = malloc(sizeof(t_list));
		if (!new_node)
			exit (1);
		new_node->index = integer;
		new_node->next = head;
		head = new_node;
	}
}
