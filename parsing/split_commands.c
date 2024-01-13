/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:23:50 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/13 17:22:56 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

/* Here I'm going to split the leftover of the commandline after extracting */
/* all redirections file names and tokenizing them, then convert them to */
/* spaces in the commandline, now I will get the commands as ***char based on */
/* the pipes */
/* example: */
/* original cmd_line: echo << "a.txt" -la | cat >> "we42.txt" -n*/
/* remove spaces cmd_line: echo            -la | cat               -n*/
/* now I will split the cmd_line as: cmds[0][0] = "echo", cmds[0][1] = "-la" */
/*                                   cmds[1][0] = "cat",  cmds[0][1] = "-n"  */

// static t_bool	is_cmd_b4_pipe(char *cmd_line)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_line[i] && cmd_line[i] != '|')
// 	{
// 		if (cmd_line[i] != ' ')
// 			return (TRUE);
// 		i++;
// 	}
// 	return (FALSE);
// }

int		*find_cmds_num(char *cmd_line)
{
	int *cmds_num;
	int	len;
	int	i;
	int	j;
	int k;
	t_bool cmd_trigger;
	t_bool quo_trigger;
	char quo_char;

	cmds_num = ft_calloc(find_parts_num(cmd_line), sizeof(int));
	len = ft_strlen(cmd_line);
	i = -1;
	j = 0;
	k = 0;
	quo_char = '\0';
	cmd_trigger = false;
	quo_trigger = false;
	while (++i < len)
	{
		if ((cmd_line[i] == '"' || cmd_line[i] == '\'') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
		}
		else if ((cmd_line[i] == quo_char) && quo_trigger)
			quo_trigger = false;
		if (cmd_line[i] == '|' && !quo_trigger)
		{
			j++;
			k = 0;
		}
		if ((cmd_line[i] == ' ' || cmd_line[i] == '|') && !quo_trigger && cmd_trigger)
			cmd_trigger = FALSE;
		if (cmd_line[i] != ' ' && cmd_line[i] != '|' && !cmd_trigger)
		{
			cmds_num[j] = ++k;
			cmd_trigger = TRUE;
		}
	}
	return (cmds_num);
}

int **find_cmds_chars_num(char *cmd_line)
{
	int	**cmds_chars_num;
	int	*cmds_num;
	int	parts_num;
	int	len;
	int	i;
	int j;
	int k;
	int chars_num;
	t_bool	quo_trigger;
	char	quo_char;

	cmds_num = find_cmds_num(cmd_line);
	parts_num = find_parts_num(cmd_line);
	len = ft_strlen(cmd_line);
	cmds_chars_num = ft_calloc(parts_num, sizeof(int *));
	i = -1;
	while (++i < parts_num)
		cmds_chars_num[i] = ft_calloc(cmds_num[i], sizeof(int));
	i = -1;
	chars_num = 0;
	j = 0;
	k = 0;
	quo_trigger = FALSE;
	quo_char = '\0';
	while (++i < len && cmd_line[i])
	{
		if ((cmd_line[i] == '"' || cmd_line[i] == '\'') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
		}
		else if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == '|' && !quo_trigger)
		{
			j++;
			k = 0;
			chars_num = 0;
		}
		if (cmd_line[i] == ' ' && (i == 0 || cmd_line[i - 1] != ' ') && (i == 0 || cmd_line[i - 1] != '|') && !quo_trigger)
		{
			k++;
			chars_num = 0;
		}
		if (((cmd_line[i] != '|' && cmd_line[i] != '"' && cmd_line[i] != '\'' && cmd_line[i] != ' ' && cmd_line[i] != '\0') || ((cmd_line[i] != ' ' || cmd_line[i] == '|' || cmd_line[i] != '"' || cmd_line[i] != '\'') && (cmd_line[i] != quo_char) && quo_trigger)))
			cmds_chars_num[j][k] = ++chars_num;
	}
	return (cmds_chars_num);
}

char	***split_cmds(char *cmd_line)
{
	char ***cmds;
	int	i;
	int j;
	int k;
	int l;
	int len;
	int	parts_num;
	int	*cmds_num;
	int **cmds_chars_num;
	t_bool	quo_trigger;
	char	quo_char;
	t_bool	cmd_trigger;

	parts_num = find_parts_num(cmd_line);
	cmds_num = find_cmds_num(cmd_line);
	// printf("ihn: %d\n", cmds_num[0]);
	cmds_chars_num = find_cmds_chars_num(cmd_line);	
	cmds = ft_calloc(parts_num + 1, sizeof(char **));
	if (!cmds)
		return (NULL);
	i = -1;
	while (++i < parts_num)
	{
		cmds[i] = ft_calloc(cmds_num[i] + 1, sizeof(char *));
		if (!cmds[i])
			return (NULL);
		j = -1;
		while (++j < cmds_num[i])
		{
			cmds[i][j] = ft_calloc(cmds_chars_num[i][j] + 1, sizeof(char));
			if (!cmds[i][j])
				return (NULL);
		}
	}
	i = -1;
	j = 0;
	k = 0;
	l = 0;
	len = ft_strlen(cmd_line);
	quo_trigger = FALSE;
	cmd_trigger = FALSE;
	quo_char = '\0';
	while (++i < len)
	{
		if ((cmd_line[i] == '"' || cmd_line[i] == '\'') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
		}
		else if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == '|' && !quo_trigger)
		{
			if (cmd_line[i - 1] != ' ')
				cmds[j][++k] = NULL;
			cmds[j][k] = NULL;
			k = 0;
			l = 0;
			j++;
		}
		if (cmd_line[i] == ' ' && (i == 0 || cmd_line[i - 1] != '|') && !quo_trigger)
		{
			k++;
			l = 0;
			cmd_trigger = FALSE;
		}
		if ((cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"') || ((cmd_line[i] == ' ' || cmd_line[i] == '|' || cmd_line[i] == '\'' || cmd_line[i] == '"') && (cmd_line[i] != quo_char) && quo_trigger))
		{
			cmds[j][k][l++] = cmd_line[i];
			if ((cmd_line[i + 1] == ' ' || cmd_line[i + 1] == '|') && !quo_trigger)
				cmds[j][k][l] = '\0';
		}
		if (cmd_line[i] == ' ' && (i == 0 || cmd_line[i - 1] != ' ') && (i == 0 || cmd_line[i - 1] != '|') && !quo_trigger && cmd_trigger)
		{
			cmds[j][k++][l] = '\0';
			cmd_trigger = FALSE;
		}
	}
	if (cmds[j])
		cmds[++j] = NULL;
	return(cmds);
}

/* to try find_cmds_num function */
// int main(void)
// {
// 	while (1)
// 	{
// 		char	*input = readline("$ ");
// 		char	*indup = ft_strdup(input);
// 		free (input);
// 		indup = delete_excess_spcs(indup);
// 		indup = conv_redir2spcs(indup);
// 		int *cmds_num = find_cmds_num(indup);
// 		int parts_num = find_parts_num(indup);
// 		printf("parts_num: %d\n", parts_num);
// 		printf("%s\n", indup);
// 		for(int i = 0; i < parts_num; i++)
// 			printf("part:[%d] --> cmds_num = %d\n", i, cmds_num[i]);
// 		free (indup);
// 	}
// 	return (0);
// }