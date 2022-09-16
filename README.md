# Introduction
Create a minimal shell in C

## Targets
Build a minimal `bash` like shell, able to handle command inputs like:
 * command with arguments
 * redirections
 * heredocs
 * pipes

And having a set of builtins like:
 * exit
 * env
 * export
 * cd
 * pwd
 * unset

## Strategy
We managed to use an AST (abstact syntax tree) and thus only have to run the
commands one after the other, with respect to their hierachy inside the tree.

We also decided to use a linked list to store our environment and thus been
able to add/remove easely any element.

This project has been an opportunity to discover more feature of the shell, and
understand how many aspects of the computer are related, and how there works,
like fds.

## Bonus
As we archived to handle all the mandatory expectations, we digged deeper in the
project, by making the following tools availables:
 * add `&&`and `||` operators
 * handle wildcards (`*`)

Given all that we also made a simplified subshell, to handle priorities bitween
logical operations and pipes.

## Some helpfull tools
Try such commands to see if you manage your file descriptors correctly:
```bash
yes | cat | cat | ... | head
```
You search which fds are leaking, take a look at the following commands to first
see how your processes are coupled one with the other, and then check their fds.
```bash
ps -AH
/proc/PID
```
Have you done enougth research about what a TTY is, what interactive mode
is. What happens if your redirect the input of bash, or it output, or it error
output ? All those tiny details make the difference.

## Thanks
Parsing, expand and data structures were made by
[fmauguin](https://github.com/Wonderworlds) as a really strong basis to allow me
create the execution scheme and the builtins.
