#!/bin/bash

dir=$(pwd)

valgrind -q --track-fds=yes --leak-check=full --trace-children=yes --suppressions=$dir/readline.supp ./minishell