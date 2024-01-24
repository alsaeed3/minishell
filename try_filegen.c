#include "inc/exec.h"

char	*generate_file_names(int pos)
{
	char	*name;
	char	*name2;
	char	*ret_name;
	char	*pos_char;
	char	*tmp;

	name = "/tmp/heredoc";
	name2 = ".tmp";
	pos_char = ft_itoa(pos);
	tmp = ft_strjoin(name, pos_char);
	free (pos_char);
	ret_name = ft_strjoin(tmp, name2);
	free (tmp);
	return (ret_name);
}

int main(void)
{
	// while (1)
	// {
		char *line = readline("> ");
		int a = ft_atoi(line, NULL);
		free (line);
		char *b = generate_file_names(a);
		printf("%s\n", b);
		free (b);
		return (0);
	// }
}