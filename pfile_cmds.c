#include "main.h"

extern string name;
extern int hist;

int pfile_cmds(string file_path, int *exe_ret);

/**
 * fail_to_open - prints an error message when a file can't be opened
 * @fl_path: path to the file
 *
 * Return: 127
 */
int fail_to_open(string fl_path)
{
	int len;
	string err, hist_s;

	hist_s = _itoa(hist);
	if (!hist_s)
		return (127);

	len = _strlen(name) + _strlen(hist_s) + _strlen(fl_path) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_s);
		return (127);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_s);
	_strcat(err, ": Can't open ");
	_strcat(err, fl_path);
	_strcat(err, "\n");

	free(hist_s);
	write(STDERR_FILENO, err, len);
	free(err);

	return (127);
}

/**
 * pfile_cmds - executes the commands in a file
 * @f_path: path to file
 * @e_value: return value of last command ran
 *
 * Return: return value of last command ran, -127 on failure, -1 on error
 */
int pfile_cmds(string f_path, int *e_value)
{
	int ret;
	unsigned int l_size = 0, o_size = 120;
	char buff[120];
	string ln, *args, *f;
	ssize_t i, fl, rd;

	hist = 0;
	fl = open(f_path, O_RDONLY);
	if (fl == -1)
	{
		*e_value = fail_to_open(f_path);
		return (*e_value);
	}
	ln = malloc(sizeof(char) * o_size);
	if (!ln)
		return (-1);
	do {
		rd = read(fl, buff, 119);
		if (rd == 0 && l_size == 0)
			return (*e_value);
		buff[rd] = '\0';
		l_size += rd;
		ln = _realloc(ln, o_size, l_size);
		_strcat(ln, buff);
		o_size = l_size;
	} while (rd);
	for (i = 0; ln[i] == '\n'; i++)
		ln[i] = ' ';
	for (; i < l_size; i++)
	{
		if (ln[i] == '\n')
		{
			ln[i] = ';';
			for (i += 1; i < l_size && ln[i] == '\n'; i++)
				ln[i] = ' ';
		}
	}
	var_repl(&ln, e_value);
	handle_line(&ln, l_size);
	args = _strtk(ln, " ");
	free(ln);
	if (!args)
		return (0);
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
			ret = call_args(args, f, e_value);
			args = &args[++i];
			i = 0;
		}
	}
	ret = call_args(args, f, e_value);
	free(f);

	return (ret);
}
