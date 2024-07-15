
## todo list

- [heredoc] check leaks for ctrl-c heredoc

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
