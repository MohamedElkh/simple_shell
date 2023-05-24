#ifndef _SHELL_H_
#define _SHELL_H_

/*
 * File: shell.h
 * Auth: Mohamed Elkharashy
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
 * struct builtin_s - struct type defining builtin commands.
 * @name: name of the builtin command.
 * @f: function to pointer to the builtin command's function.
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **frov);
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
 * struct alias_s - new struct defining aliases.
 * @name: name of the alias.
 * @value: value of the alias.
 * @next: pointer struct alias_s.
 */

typedef struct alias_s
{
	char *value;
	char *name;
	struct alias_d *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* global intergar */
int hist;

/* global string */
char *name;


/* Input Helpers */
void handleline(char **lin, ssize_t ready);
void variablereplacement(char **line, int *exret);
char *getargs(char *lin, int *exret);
int callargs(char **args, char **main, int *exret);
int runargs(char **args, char **main, int *exret);
int handleargs(int *exret);
int checkargs(char **args);
void freeargs(char **args, char **main);
char **replacealiases(char **args);


/* Main Helpers */
ssize_t _getline(char **lptr, size_t *num, FILE *stream);
void *_realloc(void *ptr, unsigned int old_value, unsigned int new_value);
char **_strtok(char *lin, char *delim);
char *getlocation(char *commands);
list_t *getpath_dir(char *paths);
int execute(char **args, char **main);
void freelist(list_t *main);
char *_itoa(int number);


/* String functions */
int _strlen(const char *str);
char *_strcat(char *desti, const char *srcs);
char *_strncat(char *desti, const char *srcs, size_t n);
char *_strcpy(char *desti, const char *srcs);
char *_strchr(char *str, char cha);
int _strspn(char *str, char *acception);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);

/* Builtin Helpers */
char **_copyenve(void);
void free_enve(void);
char **_getenv(const char *vari);

/* Builtins */
int (*get_builtin(char *commands))(char **args, char **frov);
int shell_exit(char **args, char **frov);
int shell_env(char **args, char __attribute__((__unused__)) **frov);
int shell_setenv(char **args, char __attribute__((__unused__)) **frov);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **frov);
int shell_cd(char **args, char __attribute__((__unused__)) **frov);
int shell_alias(char **args, char __attribute__((__unused__)) **frov);
int shell_help(char **args, char __attribute__((__unused__)) **frov);


/* Error Handling */
int createerror(char **args, int errx);
char *errorenv(char **args);
char *error1(char **args);
char *error2_exit(char **args);
char *error2_cd(char **args);
char *error2_syntax(char **args);
char *error126(char **args);
char *error127(char **args);

/* Linkedlist Helpers */
alias_t *addalias_end(alias_t **main, char *name, char *val);
void freealias_list(alias_t *main);
list_t *addnode_end(list_t **main, char *dire);
void freelist(list_t *main);

void helpall(void);
void helpalias(void);
void helpcd(void);
void helpexit(void);
void helphelp(void);
void helpenv(void);
void helpsetenv(void);
void helpunsetenv(void);
void helphistory(void);

int procfile_commands(char *filepath, int *exer);
#endif /* _SHELL_H_ */
