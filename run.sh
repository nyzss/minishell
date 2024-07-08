#!/bin/bash

valgrind --track-fds=yes --leak-check=full --suppressions=readline.supp ./minishell