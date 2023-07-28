#include "main.h"

int len_num(int num);

/**
 * _itoa - converts an integer to a string
 * @num: integer to convert
 *
 * Return: pointer to the converted string
 */
string _itoa(int num)
{
	int len;
	unsigned int n;
	string buf;

	len = len_num(num);
	buf = malloc(sizeof(char) * (len + 1));

	if (!buf)
		return (NULL);

	buf[len] = '\0';

	if (num < 0)
	{
		n = num * -1;
		buf[0] = '-';
	}
	else
	{
		n = num;
	}

	--len;
	do {
		buf[len] = (n % 10) + '0';
		n /= 10;
		len--;
	} while (n > 0);

	return (buf);
}

/**
 * create_err - creates an error message
 * @args: arguments passed to the command
 * @err: error value
 *
 * Return: error value
 */
int create_err(string *args, int err)
{
	string err_s;

	switch (err)
	{
	case -1:
		err_s = err_env(args);
		break;
	case 1:
		err_s = err_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			err_s = err_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			err_s = err_2_syntax(args);
		else
			err_s = err_2_cd(args);
		break;
	case 126:
		err_s = err_126(args);
		break;
	case 127:
		err_s = err_127(args);
		break;
	}

	write(STDERR_FILENO, err_s, _strlen(err_s));

	if (err_s)
		free(err_s);

	return (err);
}
