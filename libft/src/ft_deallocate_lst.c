/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deallocate_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:05:38 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/06 21:02:06 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_deallocate_lst(t_list **stack)
{
	t_list	*curr;
	t_list	*next;

	curr = *stack;
	if (*stack != NULL)
	{
		while (curr->next != NULL)
		{
			next = curr->next;
			free_set_null(curr);
			curr = next;
		}
		if (curr != NULL)
			free_set_null(curr);
	}
}
