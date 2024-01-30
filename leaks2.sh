#/!bin/bash

valgrind --suppressions=/home/vscode/src/readline.supp --track-origins=yes --leak-check=full --show-leak-kinds=all --trace-children=yes ./minishell