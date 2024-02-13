/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:16:33 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/13 20:15:01 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	free_util_1(t_parse **data)
{
	if ((*data)->fds->oldfd[0])
	{
		close((*data)->fds->oldfd[0]);
		(*data)->fds->oldfd[0] = 0;
	}
	if ((*data)->fds->oldfd[1])
	{
		close((*data)->fds->oldfd[1]);
		(*data)->fds->oldfd[1] = 0;
	}
	if ((*data)->heredoc_tmp_files && (*data)->heredocs_num)
		ft_free_array((*data)->heredoc_tmp_files);
	if ((*data)->heredoc_tmp_files)
		free_set_null((*data)->heredoc_tmp_files);
	free_set_null((*data)->pwd);
	ft_free_array((*data)->env);
	free_set_null((*data)->fds);
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

void	free_data(t_parse **data)
{
	if ((*data)->inputs_redirections)
		free_char_triple_pointer((*data)->inputs_redirections);
	if ((*data)->outputs_redirections)
		free_char_triple_pointer((*data)->outputs_redirections);
	if ((*data)->cmds)
		free_char_triple_pointer((*data)->cmds);
	// if ((*data)->heredoc_tmp_files && (*data)->heredocs_num)
	// 	ft_free_array((*data)->heredoc_tmp_files);
	if ((*data)->envs_lst)
		ft_free_lst(&(*data)->envs_lst);
	if ((*data)->inputs_tokens)
		ft_free_intarr((*data)->inputs_tokens, (*data)->parts_num);
	if ((*data)->outputs_tokens)
		ft_free_intarr((*data)->outputs_tokens, (*data)->parts_num);
	if ((*data)->in_rdr_num)
		free_set_null((*data)->in_rdr_num);
	if ((*data)->out_rdr_num)
		free_set_null((*data)->out_rdr_num);
}
