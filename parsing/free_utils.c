/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:16:33 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/11 11:37:59 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	free_util_1(t_parse **data)
{
	free_set_null((*data)->pwd);
	ft_free_array((*data)->env);
	free_set_null((*data));
}

void	ft_free_lst(t_env **stack)
{
	t_env	*curr;
	t_env	*next;

	curr = *stack;
	if (*stack != NULL)
	{
		while (curr->next != NULL)
		{
			if (curr->info)
				free_set_null(curr->info);
			if (curr->key)
				free_set_null(curr->key);
			next = curr->next;
			free_set_null(curr);
			curr = next;
		}
		if (curr != NULL)
		{
			if (curr->info)
				free_set_null(curr->info);
			if (curr->key)
				free_set_null(curr->key);
			free_set_null(curr);
		}
	}
}

void	ft_free_intarr(int **int_arr, int parts_num)
{
	size_t	i;

	if (!int_arr)
		return ;
	i = -1;
	while (++i < (size_t)parts_num)
	{
		if (int_arr[i])
			free_set_null(int_arr[i]);
	}
	free_set_null(int_arr);
}

void	free_data(t_parse **parse)
{
	if ((*parse)->inputs_redirections)
		free_char_triple_pointer((*parse)->inputs_redirections);
	if ((*parse)->outputs_redirections)
		free_char_triple_pointer((*parse)->outputs_redirections);
	if ((*parse)->cmds)
		free_char_triple_pointer((*parse)->cmds);
	if ((*parse)->heredoc_tmp_files && (*parse)->heredocs_num)
		ft_free_array((*parse)->heredoc_tmp_files);
	if ((*parse)->envs_lst)
		ft_free_lst(&(*parse)->envs_lst);
	if ((*parse)->inputs_tokens)
		ft_free_intarr((*parse)->inputs_tokens, (*parse)->parts_num);
	if ((*parse)->outputs_tokens)
		ft_free_intarr((*parse)->outputs_tokens, (*parse)->parts_num);
	if ((*parse)->in_rdr_num)
		free_set_null((*parse)->in_rdr_num);
	if ((*parse)->out_rdr_num)
		free_set_null((*parse)->out_rdr_num);
}
