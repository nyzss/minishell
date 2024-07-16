
## todo list

### Issues after 1st evaluations
- [MAJOR] Check everything with the valgring flag --show-leak-kinds=all
- [builtin] pwd/cd should update env (OLDPWD and PWD)
- [main] leaks in ctx whenver command not found
- [builtin] "exit +" and "exit 465465465432132132132132135468798795654" should be error
- [signal] CTL+\ should do core dump with exit code of 131.
- [parsing] echo $"USER" should only print "USER" without "$"
- [builtin] cd should check the return value of chdir and print err message if the dir is no longer available (ex. deleted)
- [parsing] if export a='ls' and then export b='-a', then $a$b should exec the same as "ls -a"
- [builder] leak happend in fn_create if doing "< non_existing_file" 
- [Makefile] Added dependency to headers in each file during compilation

### complete issues after 1st evaluations
- ~~[builtin] leaks in bi_add_var, need to free arg_id if it is just updating value.~~

### old finished issues
- ~~[MAJOR] norme~~
- ~~[heredoc] make heredoc in the temporary folder '/tmp/'~~
- ~~[builtin] fix error code when missing file is input in builtins~~
- ~~[builtin] exit > out1 should print exit in the terminal and shouldnt redirect~~
- ~~[exec] if permission is denied return exit code `126` (I checked in my bash-5.2, the permission denied has the exit code of 1. Let's check again in the cluster environment) -> it does have an exit code of 1, my bad~~
- ~~[exec] fix problem where if you CTRL-C from a command then the next commands echo $? value is still going to be the ctrl-c (130) code.~~
- ~~[heredoc] check leaks for ctrl-c heredoc~~
- ~~[parser] handle the case where the user inputs: `| cat`~~
- ~~[signal] cat: change the signals just after the fork (to only print '\n' to stderr) and after the child has exit, we change them back to the default state.~~
- ~~[builtin] the exit code of exit is always 13, but should be 2 or according to the number given.~~
- ~~[signal] signal handling (ctrl-\ | ctrl-c | ctrl-d)~~
- ~~[exec] command: `ls | cat | cat > out1 > out2 -e | cat | cat > out3` should behave like bash but doesnt (pipe issue)~~
- ~~[exec] fix open fd: `ls | jksdlf | cat Makefile | < ksdjfl cat`~~
- ~~[builtin] exit 5 and exit generally leaks~~
- ~~[exec] change exec file opening in child process~~
- ~~[exec] print error on command not found~~
- ~~[MAJOR][exec] rework file open and close handling.~~
	- ~~Need to check if arguments work~~
	- ~~Rework builtin handling in exec~~
- ~~[builtin] unset $HOME and do 'cd', also if '$HOME' is NULL should error too.~~
- ~~echo $? -> done~~
- ~~export ?=hello_world or 123=wow -> should error. first char should be only alphabetical or '\_', and anything that follows should be alphanumerical with '\_' as an exception.~~
- ~~fix export print~~
- ~~solved unset segfault issue~~
- ~~[builtin] exit shall print "exit" on STDOUT (before error message)~~
- ~~[builtin] unset "ZZC=" should not remove the env variable of "ZZC=asdf". Should reference the whole string not the id parsed from string.~~
- ~~[builtin] export "" should be error, but currently it will add "" as id to env.~~
- ~~[builtin] export "ZZC" if "ZZC=abc" already existed, it shall not replace the current value.~~
- ~~[builtin] the exit code of exit is always 13, but should be 2 or according to the number given.~~
- ~~[prompt] if "cat" and use ^C, there will be two promts, but should be just one prompt~~
- ~~[display] `< Makefile a | a2 | a3 | a4 | a5 | a6 > outfile` is printed in a disorderly manner~~
- ~~[exec] Different behaviour of the following cmd: "< Makefile << here cat | wc -l << there > out3 | echo yo". No calls for second here_doc and the 3rd cmd is done first.~~
- ~~[heredoc] Refactor and initiate heredoc before exec~~
- ~~[heredoc] currently the here_doc fails to unlink itself~~
- ~~[builtin] `exit -100` and `exit +100` should work~~
