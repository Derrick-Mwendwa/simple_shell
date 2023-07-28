#include "main.h"

int run_args(string *args, string *front, int *exe_ret);
int check_args(string *args);

/**
 * get_args - gets the arguments from stdin
 * @ln: buffer to store the arguments in
 * @e_value: exit value
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
string get_args(string ln, int *e_value)
{
	size_t n;
	ssize_t read;
	string prompt;

	n = 0;
	prompt = "$ ";
	if (ln)
		free(ln);
	read = _getline(&ln, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(ln, e_value));
	}
	ln[read - 1] = '\0';
	var_repl(&ln, e_value);
	handle_line(&ln, read);

	return (ln);
}

/**
 * call_args - Calls the execution of a command
 * @args: arguments
 * @f: pointer to the beginning of args
 * @e_value: exit value
 *
 * Return: return value of the last executed command
 */
int call_args(string *args, string *f, int *e_value)
{
	int r, i;

	if (!args[0])
		return (*e_value);
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			r = run_args(args, f, e_value);
			if (*e_value != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (r);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			r = run_args(args, f, e_value);
			if (*e_value == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (r);
			}
		}
	}
	args = replace_aliases(args);
	r = run_args(args, f, e_value);

	return (r);
}

/**
 * run_args - runs the execution of a command
 * @args: arguments
 * @f: pointer to the beginning of args
 * @e_value: exit value
 *
 * Return: return value of the last executed command
 */
int run_args(string *args, string *f, int *e_value)
{
	int r, i, (*builtin)(string *args, string *front);

	builtin = get_builtin(args[0]);
	if (builtin)
	{
		r = builtin(args + 1, f);
		if (r != EXIT)
			*e_value = r;
	}
	else
	{
		*e_value = execute(args, f);
		r = *e_value;
	}
	++hist;
	for (i = 0; args[i]; i++)
		free(args[i]);

	return (r);
}

/**
 * handle_args - handles the arguments provided
 * @e_value: exit value
 *
 * Return: -2 if EOF, -1 if error, 0 otherwise
 */
int handle_args(int *e_value)
{
	int r, i;
	string *args, ln, *f;

	r = 0;
	ln = NULL;
	ln = get_args(ln, e_value);
	if (!ln)
		return (_EOF);

	args = _strtk(ln, " ");
	free(ln);
	if (!args)
		return (r);
	if (check_args(args) != 0)
	{
		*e_value = 2;
		free_args(args, args);
		return (*e_value);
	}
	f = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			r = call_args(args, f, e_value);
			args = &args[++i];
			i = 0;
		}
	}
	if (args)
		r = call_args(args, f, e_value);

	free(f);
	return (r);
}

/**
 * check_args - checks for leading ';', '&&', or '||'
 * @args: arguments
 *
 * Return: -2 if found, 0 otherwise
 */
int check_args(string *args)
{
	size_t i;
	string cur, nx;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_err(&args[i], 2));
			nx = args[i + 1];
			if (nx && (nx[0] == ';' || nx[0] == '&' || nx[0] == '|'))
				return (create_err(&args[i + 1], 2));
		}
	}

	return (0);
}
