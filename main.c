/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:42 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/21 17:47:17 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
#include "../inc/parser.h"

void 	print_function(t_parse parser);

/* Test the whole parsing in int main */
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_parse	parser;
	data_init(&parser, env);
	set_signals();

    while (1) {
        char *cmd_line = readline("MINISHELL$ ");

        // Check for EOF (Ctrl+D)
        if (!cmd_line) {
            printf("\nExiting MINISHELL...\n");
            break;
        }

        add_history(cmd_line);

        char *dup = ft_strdup(cmd_line);

        if (parse_shell(dup, &parser)) {
            // Free resources and continue to the next iteration
            free(dup);
            continue;
        }

        free(dup);

        exec_delegator(&parser);

        // Uncomment the line below if you have a function to free the resources used by the parser
        // free_char_triple_pointer(inputs_names);
    }

    return 0;
}


void print_function(t_parse parser)
{
	int j;
	printf("parts_num = %d\n", parser.parts_num);
		printf("\n");
		printf("---------------------------------------------\n");
		printf("#       inputs_redirection_file_names:      #\n");
		int	i = -1;
		if (parser.inputs_redirections)
		{
			while(parser.inputs_redirections[++i])
			{
				j = -1;
				while (parser.inputs_redirections[i][++j])
					printf("-------->part:[%d], order:[%d] = {%s}\n", i, j, parser.inputs_redirections[i][j]);			
			}
		}
		printf("\n");
		printf("---------------------------------------------\n");
		printf("#                inputs_tokens:             #\n");
		i = -1;
		if (parser.in_redir_num)
		{
			while (++i < parser.parts_num)
			{
				j = -1;
				while (++j < parser.in_redir_num[i])
					printf("-------->part:[%d], order:[%d] = { %d }\n", i, j, parser.inputs_tokens[i][j]);
			}
		}
		printf("\n");
		printf("---------------------------------------------\n");
		printf("#      outputs_redirection_file_names:      #\n");
		i = -1;
		while(parser.outputs_redirections[++i])
		{
			j = -1;
			while (parser.outputs_redirections[i][++j])
				printf("-------->part:[%d], order:[%d] = {%s}\n", i, j, parser.outputs_redirections[i][j]);			
		}
		printf("\n");
		printf("---------------------------------------------\n");
		printf("#               outputs_tokens:             #\n");
		i = -1;
		while (++i < parser.parts_num)
		{
			j = -1;
			while (++j < parser.out_redir_num[i])
				printf("-------->part:[%d], order:[%d] = { %d }\n", i, j, parser.outputs_tokens[i][j]);
		}
		printf("\n");
		printf("---------------------------------------------\n");
		printf("#                   cmds:                   #\n");
		i = -1;
		while(parser.cmds[++i])
		{
			j = -1;
			while (parser.cmds[i][++j])
				printf("-------->part:[%d], order:[%d] = {%s}\n", i, j, parser.cmds[i][j]);			
		}
		printf("\n");
	
}




