/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:27:45 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/11 11:23:27 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>
# include <stdint.h>

# ifdef FALSE
#  undef FALSE
# endif
# ifdef TRUE
#  undef TRUE
# endif

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_hvr
{
	char	*line;
	int		wrfd;
	int		rdfd;
	int		i;
	int		j;
	int		k;
}	t_hvr;

typedef struct s_var
{
	int		parts_num;
	int		i;
	int		j;
	int		k;
	int		l;
	int		len;
	t_bool	qutrg;
	char	qchr;
	t_bool	rdrtrg;
	t_bool	squtrg;
	t_bool	dqutrg;
	t_bool	dlrtrg;
	char	*ret;
	char	*env;
	char	*envalu;
	int		size;
	int		expsize;
	int		cnum;
	char	*nordr;
	int		*rnum;
	int		**rcn;
	int		**tkn;
	char	***rnms;
}	t_var;

typedef struct s_cvr
{
	char	***cmds;
	int		i;
	int		j;
	int		k;
	int		l;
	int		len;
	int		parts_num;
	int		*cnum;
	int		**chrn;
	int		chars_num;
	t_bool	qutrg;
	char	quchr;
	t_bool	ctrg;
}	t_cvr;

typedef struct s_env_size
{
	int		envs_size;
}	t_env_size;

typedef struct s_env
{
	char			*key;
	char			*info;
	struct s_env	*next;
}	t_env;

typedef struct s_fd
{
	int		pfd[2];
	int		oldfd[2];
}	t_fd;

typedef struct s_parse
{
	int		parts_num;
	int		tot_inredir;
	int		*in_rdr_num;
	char	***inputs_redirections;
	int		**inputs_tokens;
	int		heredocs_num;
	int		tot_outredir;
	int		*out_rdr_num;
	char	***outputs_redirections;
	int		**outputs_tokens;
	char	***cmds;
	t_env	*envs_lst;
	t_fd	*fds;
	char	**env;
	char	**heredoc_tmp_files;
	int		fd_in;
	int		fd_out;
	char	*pwd;
	int		exit_status;
	int		h_index;
}	t_parse;

typedef struct s_main
{
	t_parse	*data;
	char	*cmd_line;
	char	*dup;
}	t_main;

typedef struct t_inf
{
	int		i;
	int		j;
	char	*info;
}	t_inf;

extern int	g_signal;

t_bool	init_rdr_vars(t_var *var, t_parse *data, char *str, char rdr);
void	quote_context(char *str, t_var *var);
t_env	*add_env(t_env *head, char *env);
t_env	*get_envs_lst(char **original_envs);
t_env	*ft_env_last(t_env *head);
char	*ft_getenv(char *key, t_env *envs);
char	*conv_tabs2spcs(char *cmd_line);
char	*delete_excess_spcs(char *cmd_line);
char	*expand_dollar_string(char *cmd_line, t_env *env_lst);
t_bool	check_pipe_redir(char *str);
t_bool	check_pipe_red_2(char *cmd_line);
void	check_pipe(t_var *var, char *str);
int		*find_rdr_num(char *str, char rdr, t_parse *data);
int		**find_rdr_chars(char *str, char rdr, t_parse *data);
char	***hold_rdr_names(char *str, char rdr, t_parse *data);
void	hold_rdr_1(t_var *var, char *str);
int		find_parts_num(char *cmd_line);
char	***malloc_rdr_names(int parts_num, int *rdr_num, int **rdr_chars);
void	free_char_triple_pointer(char ***pointer);
t_bool	check_quotes(char *cmd_line);
t_bool	check_cons_qut(t_var *var, char *str);
t_bool	cons_quot_hold(t_var *var, char *str);
t_bool	cons_quot_dollar(t_var *var, char *str);
t_bool	cons_quot_conv(t_var *var, char *str);
t_bool	cons_quot_cmd(t_cvr *cvr, char *str);
t_bool	cnsqut_cmd_num(t_cvr *cvr, char *str);
t_bool	rdr_consqut(char *str, t_var *var);
t_bool	del_consqut(char *str, t_var *var);
void	check_quout(t_var *var, char *str);
int		**tokenize_redir(char *str, t_parse *data, char rdr);
char	*conv_redir2spcs(char *cmd_line);
int		*find_cmds_num(char *cmd_line);
int		**find_cmds_chars_num(char *cmd_line);
char	***split_cmds(char *cmd_line);
t_bool	parse_shell(char *cmd_line, char *str, t_parse **data);
void	find_heredocs_num(t_parse *data);
void	handle_heredoc(t_parse *data);
char	*generate_file_names(int pos);
void	dollar_heredoc_deli(char *str, t_var *var);
t_bool	exp_dlr_cnt_1(t_var *var, char *str);
void	exp_dlr_cnt_2(t_var *var, char *str);
void	rdr_trigger(t_var *var, char *str);
void	is_dollar(t_var *var, char *str);
void	expand_dollar(t_var *var, char *str, t_env *env_lst);
void	sd_quote_trg(t_var *var, char *str);
t_bool	process_line(t_hvr *hvr, t_parse *data);
void	init_hvr(t_hvr *hvr, t_parse *data);
void	check_quot(t_var *var, char *str);
void	check_rdr(t_var *var, char *str);
t_bool	continue_conv(t_var *var, char *str);
void	fcn_cont(t_cvr *cvr, char *str);
void	count_qut_pipe(t_cvr *cvr, char *str);
void	check_qut_pipe(t_cvr *cvr, char *str);
void	malloc_cmds(t_cvr *cvr);
void	init_cvr(t_cvr *cvr, char *str, int mode);
void	exp_dlr_cnt_2(t_var *var, char *str);
void	rdr_trigger(t_var *var, char *str);
void	is_dollar(t_var *var, char *str);
void	expand_dollar(t_var *var, char *str, t_env *env_lst);
void	sd_quote_trg(t_var *var, char *str);
void	dollar_heredoc_deli(char *str, t_var *var);
void	init_dollar_vars(t_var *var, char *str, t_env *env_lst, int mode);
int		find_env_size(char *str, int i);
t_bool	null_deli(t_parse *data, t_hvr *hvr);
int		expand_dollar_count(char *str, t_env *env_lst);
void	init_del_exspc(t_var *var, char *str, int mode);
int		size_without_spcs(char *str);
void	jump_over_spaces(char *str, int *i);
void	ft_free_lst(t_env **lst);
void	free_data(t_parse **parse);
void	ft_free_intarr(int **int_arr, int parts_num);
void	check_quotation(t_var *var, char *str);
void	set_up_prompt(t_parse **data, char *cmd_line);
void	free_util_1(t_parse **data);
t_bool	check_errors(char *str);
void	if_else_conv(t_var *var, char *str);
t_bool	null_deli(t_parse *data, t_hvr *hvr);

#endif
