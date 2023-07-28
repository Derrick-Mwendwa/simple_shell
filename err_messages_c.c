#include "main.h"

/**
 * err_126 - error message for shellby_access errors
 * @args: arguments passed to the command
 *
 * Return: error string
 */
string err_126(string *args)
{
	int len;
	string err, hist_s;

	hist_s = _itoa(hist);

	if (!hist_s)
		return (NULL);

	len = _strlen(p_name) + _strlen(hist_s) + _strlen(args[0]) + 24;
	err = malloc((len + 1) * sizeof(char));
	if (!err)
	{
		free(hist_s);
		return (NULL);
	}

	_strcpy(err, p_name);
	_strcat(err, ": ");
	_strcat(err, hist_s);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Permission denied\n");

	free(hist_s);

	return (err);
}

/**
 * err_127 - error message for shellby_execve errors
 * @args: arguments passed to the command
 *
 * Return: error string
 */
string err_127(string *args)
{
	int len;
	string err, hist_s;

	hist_s = _itoa(hist);

	if (!hist_s)
		return (NULL);

	len = _strlen(p_name) + _strlen(hist_s) + _strlen(args[0]) + 16;
	err = malloc((len + 1) * sizeof(char));
	if (!err)
	{
		free(hist_s);
		return (NULL);
	}

	_strcpy(err, p_name);
	_strcat(err, ": ");
	_strcat(err, hist_s);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": not found\n");

	free(hist_s);

	return (err);
}
