#/!bin/bash

make && valgrind --suppressions=readline.supp --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell