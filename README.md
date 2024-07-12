
## todo list

- [exec] print error on command not found
- [signal] signal handling (ctrl-\ | ctrl-c | ctrl-d)
- [exec] check leaks for ctrl-c heredoc
- [exec] change exec file opening in child process
- [prompt] if "cat" and use ^C, there will be two promts, but should be just one prompt
- [builtin] export "ZZC" if "ZZC=abc" already existed, it shall not replace the current value.
- [builtin] export "" should be error, but currently it will add "" as id to env.
- [exec] the exit code of ls | exit "asdf" is 0, but should be 2.

- ~~echo $? -> done~~
- ~~export ?=hello_world or 123=wow -> should error. first char should be only alphabetical or '\_', and anything that follows should be alphanumerical with '\_' as an exception.~~
- ~~fix export print~~
- ~~solved unset segfault issue~~
- ~~[builtin] exit shall print "exit" on STDOUT (before error message)~~
- ~~[builtin] unset "ZZC=" should not remove the env variable of "ZZC=asdf". Should reference the whole string not the id parsed from string.~~
