#!/bin/bash

valgrind --track-fds=yes --leak-check=full --trace-children=yes --suppressions=readline.supp ./minishell