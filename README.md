
## todo list

- [signal] signal handling (ctrl-\ | ctrl-c | ctrl-d)
- [prompt] if "cat" and use ^C, there will be two promts, but should be just one prompt
- [exec] print error on command not found
- [exec] check leaks for ctrl-c heredoc
- [exec] change exec file opening in child process
- [exec] the exit code of ls | exit "asdf" is 0, but should be 2.
- [builtin] unset $HOME and do 'cd', also if '$HOME' is NULL should error too.

- ~~echo $? -> done~~
- ~~export ?=hello_world or 123=wow -> should error. first char should be only alphabetical or '\_', and anything that follows should be alphanumerical with '\_' as an exception.~~
- ~~fix export print~~
- ~~solved unset segfault issue~~
- ~~[builtin] exit shall print "exit" on STDOUT (before error message)~~
- ~~[builtin] unset "ZZC=" should not remove the env variable of "ZZC=asdf". Should reference the whole string not the id parsed from string.~~
- ~~[builtin] export "" should be error, but currently it will add "" as id to env.~~
- ~~[builtin] export "ZZC" if "ZZC=abc" already existed, it shall not replace the current value.~~
