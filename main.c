#include "inc/parser.h"

int main(int ac, char **av, char **env)
{
	int i = 0;
	// char *argv[] = {"PATH=/Users/alsaeed/.docker/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/alsaeed/.docker/bin:/Users/alsaeed/Downloads/42-ValgrindContainer:/Users/alsaeed/Downloads/42-ValgrindContainer", NULL};
	// char *envp[] = {NULL};
	char *envs = getenv(1);

	printf("\nenvs: %s\n", envs);
	// while (envs[i])
	// {
	// 	printf("\nenvs[%d]:\n %s\n", i, envs[i]);
	// 	i++;
	// }
	// char *in = readline("enter $>: "); 
	// printf("------->%s\n", getenv("PATHdfgb"));
	// execve("fgh", argv, envp);
		// printf("FAIL\n");
	// else
		// printf("CORRECT\n");
	// while (env[i])
	// {
	// 	printf("\nenv[%d]:\n%s\n", i, env[i]);
	// 	i++;
	// }
	return(0);
}