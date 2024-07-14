#!/bin/bash

valgrind -q --track-fds=yes --leak-check=full --trace-children=yes --suppressions=readline.supp ./minishell