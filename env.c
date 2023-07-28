#include "main.h"

/**
 * _unsetenv - removes an environmental variable
 * @args: arguments passed to the shell
 * @f: pointer to the beginning of args
 *
 * Return: 0 on success, -1 otherwise
 */
int _unsetenv(string *args, char __attribute__((__unused__)) **f)
{
	int i, j;
	string *var, *n_env;
	size_t size;

	if (!args[0])
		return (create_err(args, -1));

	var = get_env(args[0]);

	if (!var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	n_env = malloc(sizeof(string) * size);

	if (!n_env)
		return (create_err(args, -1));

	for (i = 0, j = 0; environ[i]; i++)
	{
		if (*var == environ[i])
		{
			free(*var);
			continue;
		}
		n_env[j] = environ[i];
		j++;
	}

	free(environ);
	environ = n_env;
	environ[size - 1] = NULL;

	return (0);
}

/**
 * _env - outputs the current environment variables
 * @args: arguments passed to the shell
 * @f: pointer to the beginning of args
 *
 * Return: 0 on success, -1 otherwise
 */
int _env(string *args, char __attribute__((__unused__)) **f)
{
	int i;
	char new_line = '\n';

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &new_line, 1);
	}

	(void)args;

	return (0);
}

/**
 * _setenv - sets or changes an environmental variable
 * @args: arguments passed to the shell
 * @f: pointer to the beginning of args
 *
 * Return: 0 on success, -1 otherwise
 */
int _setenv(string *args, char __attribute__((__unused__)) **f)
{
	int index;
	string *var, *n_env, n_val;
	size_t size;

	var = NULL;

	if (!args[0] || !args[1])
		return (create_err(args, -1));
	n_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!n_val)
		return (create_err(args, -1));
	_strcpy(n_val, args[0]);
	_strcat(n_val, "=");
	_strcat(n_val, args[1]);
	var = get_env(args[0]);
	if (var)
	{
		free(*var);
		*var = n_val;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;
	n_env = malloc(sizeof(string) * (size + 2));
	if (!n_env)
	{
		free(n_val);
		return (create_err(args, -1));
	}
	for (index = 0; environ[index]; index++)
		n_env[index] = environ[index];
	free(environ);
	environ = n_env;
	environ[index] = n_val;
	environ[index + 1] = NULL;

	return (0);
}
