/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/06 21:49:47 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/exec.h"

int	g_signal = 0; 

int main(int ac, char **av, char **env)
{
	t_parse	*parser;
	char	*cmd_line;
	char	*dup;
	(void)ac;
	(void)av;

	if (init_main(&parser, &dup, env))
		return (1);
	while (1)
	{
		set_signals(&parser);
		if (data_reset(&parser))
			continue ;
		cmd_line = readline("minishell$ ");
		set_up_prompt(&parser, &dup, cmd_line);
		if (parse_shell(dup, &parser))
			continue ;
		exec_delegator(parser);
		free_parser(&parser);
	}
	free_util_1(&parser);
	return (0);
}

int		init_main(t_parse **parser, char **dup, char **env)
{
	parser = NULL;
	dup = NULL;
	if (ft_calloc_pro((&parser, 1 , sizeof(t_parse))))
		return (1);
	if (!parser)
		return (1);
	if (data_init(parser, env))
		return (1);
	return (0);
}

void	set_up_prompt(t_parse **parser, char **dup, char *cmd_line)
{
	if (g_signal == 99)
		(*parser)->exit_status = 1;
	g_signal = 1;
	if (cmd_line == NULL)
	{
		printf("exit\n");
		rl_clear_history();
		free_util_1(&*parser);
		exit(0);
	}
	add_history(cmd_line);
	if (g_signal == 99)
		(*parser)->exit_status = 1;
	*dup = ft_strdup(cmd_line);
}

void	free_util_1(t_parse **parser)
{
	free_set_null((*parser)->pwd);
	ft_free_array((*parser)->env);
	free_set_null((*parser));
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

void ft_free_intarr(int **int_arr, int parts_num)
{
    size_t i;

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



void	free_parser(t_parse **parse)
{
	free_char_triple_pointer((*parse)->inputs_redirections);
	free_char_triple_pointer((*parse)->outputs_redirections);
	free_char_triple_pointer((*parse)->cmds);
	ft_free_array((*parse)->heredoc_tmp_files);
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

//ls -la | wc| cat <<w >v
//echo hi > x | <<aa cat >>x
//<<aa cat >a|<<bb cat >>a   // working ok
//ls > a | <<bb cat >>a // not appending
//<a cat > b | <<vv cat >>b // not appending
//<<aa <a cat > b | <<vv cat >>b // not appending
// 
