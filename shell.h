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

extern char **environment;
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

void _removalhash(char *loc);
char *_takeline(void);
char *_envget(char *str);
char *p_build(char *val, char *tok);
int _search_cmd(char **c);

int bul_echo(int str, char **cm);
int env_display(__attribute__((unused)) int last, __attribute__((unused)) char **cmm);
int dis_env_help(__attribute__((unused)) int last, char **cmm);
int dir_change(__attribute__((unused)) int last, char **cmd);
void built_exit(int s, char **cmd, char *input, char **argv);

#endif
