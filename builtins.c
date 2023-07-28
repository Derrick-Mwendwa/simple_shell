#include "main.h"

int s_exit(string *args, string *f);
int _cd(string *args, char __attribute__((__unused__)) **f);
int _help(string *args, char __attribute__((__unused__)) **f);

/**
 * get_builtin - compares a command with the builtin functions
 * @cmd: command to match
 *
 * Return: pointer to matching function
 */
int (*get_builtin(string cmd))(string *args, string *f)
{
	int i;
	builtin functions[] = {
		{"alias", _alias},
		{"cd", _cd},
		{"env", _env},
		{"exit", s_exit},
		{"help", _help},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}};

	for (i = 0; functions[i].name; i++)
	{
		if (_strcmp(functions[i].name, cmd) == 0)
			break;
	}

	return (functions[i].fun);
}

/**
 * s_exit - exits the shellby
 * @args: arguments to exit with
 * @f: pointer to the beginning of args
 *
 * Return: -3 if no arguments, 2 if too many arguments, or the exit value
 */
int s_exit(string *args, string *f)
{
	int i, len;
	unsigned int n, max;

	len = 10;
	n = 0;
	max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len && args[0][i] >= '0' && args[0][i] <= '9')
			{
				n = (n * 10) + (args[0][i] - '0');
			}
			else
			{
				return (create_err(--args, 2));
			}
		}
	}
	else
	{
		return (-3);
	}

	if (n > max - 1)
		return (create_err(--args, 2));

	args -= 1;
	free_args(args, f);
	free_env();
	free_alias_list(aliases);
	exit(n);
}

/**
 * _cd - changes the current working directory
 * @args: array of arguments
 * @f: pointer to the beginning of args
 *
 * Return: -2 if too many arguments, -1 if an error occurs, or 0 on success
 */
int _cd(string *args, char __attribute__((__unused__)) **f)
{
	string *dir_inf, n_line = "\n";
	string o_pwd = NULL, pwd = NULL;
	struct stat dir;

	o_pwd = getcwd(o_pwd, 0);

	if (!o_pwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
				args[0][1] == '\0')
			{
				if (get_env("OLDPWD") != NULL)
					(chdir(*get_env("OLDPWD") + 7));
			}
			else
			{
				free(o_pwd);
				return (create_err(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode) &&
				((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(o_pwd);
				return (create_err(args, 2));
			}
		}
	}
	else
	{
		if (get_env("HOME") != NULL)
			chdir(*(get_env("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);

	if (!pwd)
		return (-1);

	dir_inf = malloc(sizeof(string) * 2);

	if (!dir_inf)
		return (-1);

	dir_inf[0] = "OLDPWD";
	dir_inf[1] = o_pwd;

	if (_setenv(dir_inf, dir_inf) == -1)
		return (-1);

	dir_inf[0] = "PWD";
	dir_inf[1] = pwd;

	if (_setenv(dir_inf, dir_inf) == -1)
		return (-1);

	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, n_line, 1);
	}

	free(o_pwd);
	free(pwd);
	free(dir_inf);

	return (0);
}

/**
 * _help - prints the help information for a builtin
 * @args: array of arguments
 * @f: pointer to the beginning of args
 *
 * Return: 0 on success, -1 if no help information is available
 */
int _help(string *args, char __attribute__((__unused__)) **f)
{
	if (!args[0])
		h_all();
	else if (_strcmp(args[0], "alias") == 0)
		h_alias();
	else if (_strcmp(args[0], "cd") == 0)
		h_cd();
	else if (_strcmp(args[0], "exit") == 0)
		h_exit();
	else if (_strcmp(args[0], "env") == 0)
		h_env();
	else if (_strcmp(args[0], "setenv") == 0)
		h_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		h_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		h_help();
	else
		write(STDERR_FILENO, p_name, _strlen(p_name));

	return (0);
}
