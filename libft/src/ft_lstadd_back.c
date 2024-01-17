/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:46:27 by alsaeed           #+#    #+#             */
/*   Updated: 2023/10/12 11:31:10 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstadd_back(t_list *head, int integer)
{
	t_list	*last_node;
	t_list	*new_node;

	if (head == NULL)
	{
		new_node = (t_list *)malloc(sizeof(t_list) * 1);
		new_node->data = integer;
		new_node->index = -1;
		new_node->next = NULL;
		head = new_node;
		return (head);
	}
	if (head != NULL)
	{
		last_node = ft_lst_last(head);
		new_node = (t_list *)malloc(sizeof(t_list));
		if (!new_node)
			exit(1);
		new_node->data = integer;
		new_node->index = -1;
		new_node->next = NULL;
		last_node->next = new_node;
	}
	return (head);
}
