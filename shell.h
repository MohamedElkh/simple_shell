#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>

#define BUF_SIZE 1024
#define P_PRINT(s) (write(STDOUT_FILENO, s,_stringlength(s)))
#define DELI " \t\r\n\a"

extern char **environ;
int _stringlength(char *str);
int _putchar(char c);
void _pputs(char *s);
int p_atoi(char *str);
char *_strncopy(char *desti, char *src, int num);
int strncompare(const char *str, const char *str2, unsigned int num);
char *_strconcat(char *desti, char *src);
char *strchara(char *str, char cc);
char *strcopy(char *desti, char *src);
char *_duplicatestr(char *s);               
void rev_arr(char *array, int le);              
int _lengthint(int n);                            
int _charaisa(int n);                             
int _comparestr(char *str, char *str2);        
char *p_itoa(size_t num);          
void p_number(size_t num);
void p_num(int num);
void prin_error(int n, char **cm, char **argv);
void display_error(int count, char *inp, char **argv);
void p_pro(void);
size_t ch_del(char cc, const char *s);
char *strtoken(char *s, const char *deli);
char **func_pasre(char *inp);

char *_copymem(char *src, char *desti, size_t num);
void _arrfree(char *ch, char **cm);
void *_locatemem(unsigned int value);
void *arr_filled(int n, unsigned int le, void *p);
void *fre_locate(void *p, size_t oldvalue, size_t newvalue);

void _removalhash(char *bf);
char *_takeline();
char *_envget(char *str);
char *p_build(char *val, char *tok);
int _search_cmd(char **c);
/* b_t functions to be checked */
int bul_echo(char **cm, int str);
int env_display(char **cmm, int last);
int dis_env_help(char **cmm, int last);
int dir_change(char **cmd, int last);

void built_exit(int s, char **cmd, char *input, char **argv);
int echo_print(char **cm);
int display_history(char **cc, int ss);
void enviro_free(char **en);
int fun_history(char *inp);

void f_signal_handel(int n);
int func_cmd_check(int n, char *inp, char **cmd, char **argv);
/* function to handle the functions */
int f_handle_built(char **cmd, int last);

void c_arr_envi(char **env);
void exit_shell(char *li, char **cmd, FILE *file);
int func_built_check(char **cm);
void check_t_file(int count, char *li, char **argv, FILE *file);
void func_file_read(char *name, char **argv);

/**
 * struct built - built to handle and excute
 * @str: the pointer to char
 * f: function to excute 
 */

typedef struct built
{
	char *str;
	int (*f)(char **chara, int number);
} b_t;

int _strlen(char *str);
void _puts(char *s);
int _atoi(char *str);
char *_strncpy(char *desti, char *src, int num);
void array_rev(char *array, int le);
int _intlen(int n);
int _isalpha(int n);
int _strcmp(char *str, char *str2);
char *_itoa(size_t num);
char *_strchr(char *str, char cc);
char *_strcpy(char *desti, char *sr);
int _strncmp(const char *str, const char *str2, unsigned int num);
char *_strcat(char *desti, char *sr);
char *_strdup(char *s);
char *_strtok(char *s, const char *deli);
size_t ch_del(char cc, const char *s);
void built_exit(int s, char **cmd, char *input, char **argv);
int dir_change(char **cmd, __attribute__((unused)) int last);
void prompt(void);
char *_memcpy(char *src, char *desti, size_t num);
void *_calloc(unsigned int value);
char *_getline();
#endif
