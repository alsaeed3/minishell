#/!bin/bash

valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell