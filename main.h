#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define _EOF -2
#define EXIT -3

typedef char *string;

extern string *environ;
extern string name;
extern int hist;

/**
 * struct list_s - singly linked list of directory paths
 * @dir: dir path
 * @next: pointer to next node
 */
typedef struct list_s
{
	string dir;
	struct list_s *next;
} list_t;

/**
 * struct built_in - struct for builtin commands
 * @name: name of builtin command
 * @fun: function pointer to builtin command
 */
typedef struct built_in
{
	string name;
	int (*fun)(string *argv, string *f);
} builtin;

/**
 * struct alias - struct for aliases
 * @name: name of alias
 * @val: value of alias
 * @next: pointer to next node
 */
typedef struct alias
{
	string name;
	string val;
	struct alias *next;
} alias;

extern alias *aliases;

string *copy_env(void);
int execute(string *args, string *f);
int pfile_cmds(string f_path, int *e_value);
int handle_args(int *e_value);
list_t *get_path_dir(string path);
string *_strtk(string line, string delim);
string get_location(string command);
void free_alias_list(alias *head);
void free_env(void);
void *_realloc(void *p, unsigned int o_size, unsigned int n_size);
void free_list(list_t *head);
void handle_line(string *ln, ssize_t read);
void var_repl(string *ln, int *e_status);
void logical_ops(string ln, ssize_t *n_len);
void free_args(string *args, string *front);
ssize_t _getline(string *lineptr, size_t *n, FILE *stream);
ssize_t get_new_len(string ln);
string _itoa(int num);
string get_pid(void);
string get_env_val(string x, int len);
string get_args(string ln, int *e_value);
int call_args(string *args, string *f, int *e_value);
int run_args(string *args, string *f, int *e_value);
int check_args(string *args);
int _strlen(const string s);
string *replace_aliases(string *args);
string _strcat(string dest, const string src);
string _strncat(string dest, const string src, size_t n);
string _strcpy(string dest, const string src);
string _strchr(string s, char c);
void h_all(void);
void h_alias(void);
void h_cd(void);
void h_exit(void);
void h_help(void);
void h_env(void);
void h_setenv(void);
void h_unsetenv(void);
int _strspn(string s, string accept);
int _strcmp(string s1, string s2);
int _strncmp(const string s1, const string s2, size_t n);
int (*get_builtin(string cmd))(string *args, string *f);
int s_exit(string *args, string *f);
int _env(string *args, char __attribute__((__unused__)) **f);
int _setenv(string *args, char __attribute__((__unused__)) **f);
int _unsetenv(string *args, char __attribute__((__unused__)) **f);
int _cd(string *args, char __attribute__((__unused__)) **f);
int _alias(string *args, char __attribute__((__unused__)) **f);
int _help(string *args, char __attribute__((__unused__)) **f);
int len_num(int num);
int create_err(string *args, int err);
string *get_env(const string var);
string err_env(string *args);
string err_2_exit(string *args);
string err_1(string *args);
string err_2_syntax(string *args);
string err_2_cd(string *args);
string err_126(string *args);
string err_127(string *args);
alias *add_alias_e(alias **head, string name, string value);
list_t *add_node_e(list_t **head, string dir);
void free_list(list_t *head);

#endif
