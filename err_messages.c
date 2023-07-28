#include "main.h"

extern string name;
extern int hist;

/**
 * err_1 - error message for shellby_alias errors
 * @args: arguments passed to the command
 *
 * Return: error string
 */
string err_1(string *args)
{
	int len;
	string err;

	len = _strlen(name) + _strlen(args[0]) + 13;
	err = malloc((len + 1) * sizeof(char));

	if (!err)
		return (NULL);

	_strcpy(err, "alias: ");
	_strcat(err, args[0]);
	_strcat(err, " not found\n");

	return (err);
}

/**
 * err_env - error message for shellby_env errors
 * @args: arguments passed to the command
 *
 * Return: error string
 */
string err_env(string *args)
{
	int len;
	string err, hist_s;

	hist_s = _itoa(hist);

	if (!hist_s)
		return (NULL);

	--args;

	len = _strlen(name) + _strlen(hist_s) + _strlen(args[0]) + 45;
	err = malloc((len + 1) * sizeof(char));

	if (!err)
	{
		free(hist_s);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_s);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Unable to add/remove from environment\n");

	free(hist_s);

	return (err);
}

/**
 * err_2_exit - error message for shellby_exit errors
 * @args: arguments passed to the command
 *
 * Return: error string
 */
string err_2_exit(string *args)
{
	int len;
	string err, hist_s;

	hist_s = _itoa(hist);

	if (!hist_s)
		return (NULL);

	len = _strlen(name) + _strlen(hist_s) + _strlen(args[0]) + 27;
	err = malloc((len + 1) * sizeof(char));
	if (!err)
	{
		free(hist_s);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_s);
	_strcat(err, ": exit: Illegal number: ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(hist_s);

	return (err);
}

/**
 * err_2_cd - error message for shellby_cd errors
 * @args: arguments passed to the command
 *
 * Return: error string
 */
string err_2_cd(string *args)
{
	int len;
	string err, hist_s;

	hist_s = _itoa(hist);

	if (!hist_s)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(hist_s) + _strlen(args[0]) + 24;
	err = malloc((len + 1) * sizeof(char));
	if (!err)
	{
		free(hist_s);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_s);
	if (args[0][0] == '-')
		_strcat(err, ": cd: Illegal option ");
	else
		_strcat(err, ": cd: can't cd to ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(hist_s);

	return (err);
}

/**
 * err_2_syntax - error message for syntax errors
 * @args: arguments passed to the command
 *
 * Return: error string
 */
string err_2_syntax(string *args)
{
	int len;
	string err, hist_s;

	hist_s = _itoa(hist);

	if (!hist_s)
		return (NULL);

	len = _strlen(name) + _strlen(hist_s) + _strlen(args[0]) + 33;
	err = malloc((len + 1) * sizeof(char));
	if (!err)
	{
		free(hist_s);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_s);
	_strcat(err, ": Syntax error: \"");
	_strcat(err, args[0]);
	_strcat(err, "\" unexpected\n");

	free(hist_s);

	return (err);
}
