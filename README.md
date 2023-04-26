# Simple Shell

### Introduction
This repository is a [ALX School]Project. The school project consisted in writing a shell like sh (Bourne Shell) by Stephen Bourne  , 
in **C**, using a limited number of standard library functions, So Instead we used ower own function that we rewrited over the past three month 

The goal in this project was to make us understand how a shell works. To single out some items: what is the *environment*, the difference between *functions* and *system calls*, how to create *processes* using `execve`...  

## Usage 
In order to run this program, 

Clone This Repo

`` git clone https://github.com/Theemiss/simple_shell ``

compile it with  

`gcc 4.8.4 -Wall -Werror -Wextra -pedantic *.c -o hsh`.  
You can then run it by invoking `./hsh` in that same directory.  

### How to use it
In order to use this shell, in a terminal, first run the program:    
`prompt$ ./hsh`  
It wil then display a simple prompt and wait for commands.  
`$ `   
A command will be of the type `$ command`  
This shell can handle two types of commands: builtins and normal program.
##### List of built-ins
Currently the list of built-ins I wrote is:  
* cd [directory]  
Switch to the specified directory (path).
* env  
Displays the environment variable
* exit [exitstatus]  
Exit from the program with exitstatus value. 0 by default.
* getenv NAME  
Return the value of the NAME variable if it is in the environment
* help [command]  
Displays the syntax for the command, or all commands.  
* history  
Displays the last typed user .
* echo [$$] or [$?] or [$PATH]
Return pid and exit statue and PATH.
##### Command
Basicly Every Program in `$PATH`
It Support Single Word like `ls` 

It Handle Path `ls /tmp`

it Handle Options Like `ls -l`

it Handle All Three Togther Like `ls -l /var `

it Handle Command Path Also Like `/bin/ls` And All The Option And Path Like `/bin/ls -l /var`

it Handle Comments **#** 

### Exmples Builtin
...

**case env and exit**
Username@your-regular-prompt:~$ ./hsh
USER=julien
LANGUAGE=en_US
SESSION=ubuntu
COMPIZ_CONFIG_PROFILE=ubuntu
SHLVL=1
HOME=/home/julien
C_IS=Fun_:)
DESKTOP_SESSION=ubuntu
LOGNAME=julien
TERM=xterm-256color
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DISPLAY=:0
$ exit
Username@your-regular-prompt:~$ 

```
**Case Exit Statue**
```
Username@your-regular-prompt:~$ ./hsh
$ exit 98
Username@your-regular-prompt:~$ echo $?
98
Username@your-regular-prompt:~$

```
Keep Exploring The echo Builtin and history ... Using The Help Builtin

### Also
* Handle Ctrl+C: your shell should not quit when the user inputs ^C
* If no argument is given to cd the command must be interpreted like cd $HOME
* handle the command cd -
* Handle variables replacement
* Handle the $? variable
* Handle the $$ variable
* Handle The Argument file like `./hsh test` Where test is a file filled with command and builtin to excute.
### List of functions and system calls we could use
List of allowed functions and system calls

    access (man 2 access)
    chdir (man 2 chdir)
    close (man 2 close)
    closedir (man 3 closedir)
    execve (man 2 execve)
    exit (man 3 exit)
    _exit (man 2 _exit)
    fflush (man 3 fflush)
    fork (man 2 fork)
    free (man 3 free)
    getcwd (man 3 getcwd)
    getline (man 3 getline)
    getpid (man 2 getpid)
    isatty (man 3 isatty)
    kill (man 2 kill)
    malloc (man 3 malloc)
    open (man 2 open)
    opendir (man 3 opendir)
    perror (man 3 perror)
    read (man 2 read)
    readdir (man 3 readdir)
    signal (man 2 signal)
    stat (__xstat) (man 2 stat)
    lstat (__lxstat) (man 2 lstat)
    fstat (__fxstat) (man 2 fstat)
    strtok (man 3 strtok)
    wait (man 2 wait)
    waitpid (man 2 waitpid)
    wait3 (man 2 wait3)
    wait4 (man 2 wait4)
    write (man 2 write)
### Custom Function (Recreation of Standard Function in C)
* _stringlength
* _putchar
* _pputs
* p_atoi
* _strncopy
* strncompare
* _strconcat
* strchara
* strcopy
* _duplicatestr
* rev_arr
* _lengthint
* _charaisa
* _comparestr
* p_itoa
* p_number
* p_num
* prin_error
* display_error
* p_pro
* t ch_del
* strtoken
* func_pasre
* _copymem
* _arrfree
* _locatemem
* arr_filled
* fre_locate
* _removalhash
* _takeline



 
For More Info About It Check The Man Page by
```
Username@your-regular-prompt:~$ man ./man_1_simple_shell
```
Project Done in 13 Day

## Authors
* Mohamed Elkharashy [MohamedElkh](https://github.com/MohamedElkh)


