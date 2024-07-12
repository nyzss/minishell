
## todo list

- print error on command not found
- signal handling (ctrl-\ | ctrl-c | ctrl-d)
- check leaks for ctrl-c heredoc
- change exec file opening in child process

- ~~echo $? -> done~~
- ~~export ?=hello_world or 123=wow -> should error. first char should be only alphabetical or '\_', and anything that follows should be alphanumerical with '\_' as an exception.~~
- ~~fix export print~~
- ~~solved unset segfault issue~~