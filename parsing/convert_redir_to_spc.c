/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir_to_spc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:03:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/13 16:03:01 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
/* In this function I'm converting all the redirections symbols with their */
/* file names to spaces in the command line after saving all the file names */
/* with their tokens */

int	count_size_without_redir(char *cmd_line)
{
	char *no_redir;
	int	len;
	int i;
	int j;
	t_bool	redi_trigger;
	t_bool	quo_trigger;
	char	quo_char;

	redi_trigger = FALSE;
	quo_trigger = FALSE;
	len = ft_strlen(cmd_line);
	no_redir = ft_calloc((len + 1), sizeof(char));
	if (!no_redir)
		exit (1);
	i = -1;
	j = 0;
	while (++i < len && cmd_line[i])
	{
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			j++;
		}
		else if((cmd_line[i] == quo_char) && quo_char)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			j++;
		}
		if (i < len - 1 && ((cmd_line[i] == '<' && cmd_line[i + 1] != '<' && (i == 0 || cmd_line[i - 1] != '<')) || (cmd_line[i] == '>' && cmd_line[i + 1] != '>' && (i == 0 || cmd_line[i - 1] != '>'))) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			j++;
			if (cmd_line[i] == ' ')
				j++;
		}
		else if (i < len - 1 && ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') || (cmd_line[i] == '>' && cmd_line[i + 1] == '>')) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			j += 2;
			if (cmd_line[i] == ' ')
				j++;
		}
		if (cmd_line[i] == ' '  && (i == 0 || cmd_line[i - 1] != '<') && (i == 0 || cmd_line[i - 1] != '>') && redi_trigger && !quo_trigger)
		{
			j++;
			redi_trigger = FALSE;
		}
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			j++;
			continue;
		}
		if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			j++;
			continue;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"') && !quo_trigger && redi_trigger))
		{
			j++;
			continue ;
		}
		j++;
	}
	return (j);
}

char *conv_redir2spcs(char *cmd_line)
{
	char *no_redir;
	int	len;
	int	size_without_redir;
	int i;
	int j;
	t_bool	redi_trigger;
	t_bool	quo_trigger;
	char	quo_char;

	redi_trigger = FALSE;
	quo_trigger = FALSE;
	size_without_redir = count_size_without_redir(cmd_line);
	no_redir = ft_calloc((size_without_redir + 1), sizeof(char));
	if (!no_redir)
		exit (1);
	len = ft_strlen(cmd_line);
	i = -1;
	j = 0;
	while (++i < len && cmd_line[i])
	{
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			if (redi_trigger)
			{
				i++;
				no_redir[j++] = ' ';
			}
			else
				no_redir[j++] = cmd_line[i++];
		}
		else if((cmd_line[i] == quo_char) && quo_char)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			if (redi_trigger)
			{
				i++;
				no_redir[j++] = ' ';
			}
			else
				no_redir[j++] = cmd_line[i++];
		}
		if (i < len - 1 && ((cmd_line[i] == '<' && cmd_line[i + 1] != '<' && (i == 0 || cmd_line[i - 1] != '<')) || (cmd_line[i] == '>' && cmd_line[i + 1] != '>' && (i == 0 || cmd_line[i - 1] != '>'))) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			i++;
			no_redir[j++] = ' ';
			if (cmd_line[i] == ' ')
				no_redir[j++] = ' ';
		}
		else if (i < len - 1 && ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') || (cmd_line[i] == '>' && cmd_line[i + 1] == '>')) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			i += 2;
			no_redir[j++] = ' ';
			no_redir[j++] = ' ';
			if (cmd_line[i] == ' ')
				no_redir[j++] = ' ';
		}
		if ((cmd_line[i] == '|' || (cmd_line[i] == ' ' && (i == 0 || cmd_line[i - 1] != '<') && (i == 0 || cmd_line[i - 1] != '>'))) && redi_trigger && !quo_trigger)
		{
			if (cmd_line[i] == ' ')
				no_redir[j++] = ' ';
			redi_trigger = FALSE;
		}
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			if (redi_trigger)
				no_redir[j++] = ' ';
			else
				no_redir[j++] = cmd_line[i];
			continue;
		}
		if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			if (redi_trigger)
				no_redir[j++] = ' ';
			else
				no_redir[j++] = cmd_line[i];
			continue;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"') && !quo_trigger && redi_trigger))
		{
			no_redir[j++] = ' ';
			continue ;
		}
		if (!redi_trigger)
			no_redir[j++] = cmd_line[i];
		else if (cmd_line[i] != ' ' && redi_trigger)
			no_redir[j++] = ' ';
	}
	if (no_redir[j])
		no_redir[++j] = '\0';
	return (no_redir);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		char *read = readline("$> ");
// 		char *input = ft_strdup(read);
// 		// input = delete_excess_spcs(input);
// 		printf("%s\n", input);
// 		char *no_redir = conv_redir2spcs(input);
// 		free (input);
// 		printf("%s\n", no_redir);
// 		free (no_redir);
// 	}
// }
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:03:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/20 18:11:57 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	init_nordr_vars(t_var *var, char *str)
{
	var->rdrtrg = FALSE;
	var->qutrg = FALSE;
	var->len = ft_strlen(str);
	var->i = -1;
	var->size = 0;
	var->size = ft_strlen(str);
	var->nordr = ft_calloc((var->size + 1), sizeof(char));
}

char	*conv_redir2spcs(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_nordr_vars(&var, str);
	while (var.i < var.len && str[++var.i])
	{
		if (cons_quot_conv(&var, str) || check_quotation(&var, str))
			continue ;
		check_rdr(&var, str);
		check_pipe(&var, str);
		if (continue_conv(&var, str))
			continue ;
		if (!var.rdrtrg && var.i < var.len)
			var.nordr[var.j++] = str[var.i];
		else if (var.i < var.len && str[var.i] != ' ' && var.rdrtrg)
			var.nordr[var.j++] = ' ';
	}
	if (var.nordr && var.nordr[var.j])
		var.nordr[var.j] = '\0';
	free_set_null((void **)&str);
	return (var.nordr);
}
>>>>>>> main
