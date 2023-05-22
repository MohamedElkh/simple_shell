#ifndef _SHELL_H_
#define _SHELL_H_

/*
 * File: shell.h
 * Auth: Mohamed Elkharashy
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define EXIT -3
#define END_OF_FILE -2


/* Global environemnt */
extern char **environ;


/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;


/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *value;
	char *name;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* global intergar */
int hist;

/* global string */
char *name;


/* Input Helpers */
void handleline(char **line, ssize_t read);
void variablereplacement(char **args, int *exe_ret);
char *getargs(char *line, int *exe_ret);
int callargs(char **args, char **front, int *exe_ret);
int runargs(char **args, char **front, int *exe_ret);
int handleargs(int *exe_ret);
int checkargs(char **args);
void freeargs(char **args, char **front);
char **replacealiases(char **args);


/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *getlocation(char *command);
list_t *getpath_dir(char *path);
int execute(char **args, char **front);
void freelist(list_t *head);
char *_itoa(int num);


/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtin Helpers */
char **_copyenve(void);
void free_enve(void);
char **_getenv(const char *var);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_alias(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);


/* Error Handling */
int createerror(char **args, int err);
char *errorenv(char **args);
char *error1(char **args);
char *error2_exit(char **args);
char *error2_cd(char **args);
char *error2_syntax(char **args);
char *error126(char **args);
char *error127(char **args);

/* Linkedlist Helpers */
alias_t *addalias_end(alias_t **head, char *name, char *value);
void freealias_list(alias_t *head);
list_t *addnode_end(list_t **head, char *dir);
void freelist(list_t *head);

void helpall(void);
void helpalias(void);
void helpcd(void);
void helpexit(void);
void helphelp(void);
void helpenv(void);
void helpsetenv(void);
void helpunsetenv(void);
void helphistory(void);

int procfile_commands(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */
