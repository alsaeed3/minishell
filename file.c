#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main ()
{
	
	char *s = malloc(100);
	s[100000]  = 's';
	s[1000]  = 's';
	s[INT_MAX]  = 's';
	return (0);
}
