#include "main.h"

/**
 * free_env - frees the environment
 *
 * Return: void
 */
void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);

	free(environ);
}

/**
 * copy_env - copies the environment
 *
 * Return: new environment on success, NULL on failure
 */
string *copy_env(void)
{
	int i;
	string *n_env;
	size_t size;

	for (size = 0; environ[size]; size++)
		;

	n_env = malloc((size + 1) * sizeof(string));

	if (!n_env)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		n_env[i] = malloc(_strlen(environ[i]) + 1);
		if (!n_env[i])
		{
			for (i--; i >= 0; i--)
				free(n_env[i]);
			free(n_env);
			return (NULL);
		}
		_strcpy(n_env[i], environ[i]);
	}
	n_env[i] = NULL;

	return (n_env);
}

/**
 * get_env - gets an environmental variable
 * @var: the environmental variable to get
 *
 * Return: pointer to the environmental variable, NULL if not found
 */
string *get_env(const string var)
{
	int i, len;

	len = _strlen(var);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], len) == 0)
			return (&environ[i]);
	}

	return (NULL);
}
