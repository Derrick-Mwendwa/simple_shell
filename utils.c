#include "main.h"

ssize_t get_new_len(string ln);

/**
 * len_num - returns length of a number
 * @num: number to check
 *
 * Return: length of number
 */
int len_num(int num)
{
	int len;
	unsigned int n;

	len = 1;

	if (num < 0)
	{
		len++;
		n = num * -1;
	}
	else
	{
		n = num;
	}
	while (n > 9)
	{
		len++;
		n /= 10;
	}

	return (len);
}

/**
 * get_pid - gets current process ID
 *
 * Return: current process ID or NULL if failed
 */
string get_pid(void)
{
	size_t i = 0;
	string buff;
	ssize_t fl;

	fl = open("/proc/self/stat", O_RDONLY);
	if (fl == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(fl);
		return (NULL);
	}
	read(fl, buff, 120);
	while (buff[i] != ' ')
		i++;
	buff[i] = '\0';

	close(fl);
	return (buff);
}

/**
 * get_env_val - gets the value of an environmental variable
 * @x: environmental var to search for
 * @len: len of var
 *
 * Return: value of environmental variable or empty string if not found
 */
string get_env_val(string x, int len)
{
	string *addr, repl, temp, var;

	repl = NULL;
	var = malloc(len + 1);

	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, x, len);

	addr = get_env(var);
	free(var);
	if (addr)
	{
		temp = *addr;
		while (*temp != '=')
			temp++;
		temp++;
		repl = malloc(_strlen(temp) + 1);
		if (repl)
			_strcpy(repl, temp);
	}

	return (repl);
}

/**
 * get_new_len - gets the new length of the line
 * @ln: line to check
 *
 * Return: new length of line
 */
ssize_t get_new_len(string ln)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; ln[i]; i++)
	{
		current = ln[i];
		next = ln[i + 1];
		if (current == '#')
		{
			if (i == 0 || ln[i - 1] == ' ')
			{
				ln[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && ln[i - 1] != ' ' && ln[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (ln[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (ln[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&ln[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && ln[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * logical_ops - checks for logical operators
 * @ln: pointer to line in get_new_len function
 * @n_len: pointer to new_len in get_new_len function
 *
 * Return: void
 */
void logical_ops(string ln, ssize_t *n_len)
{
	char prev, cur, nxt;

	prev = *(ln - 1);
	cur = *ln;
	nxt = *(ln + 1);

	if (cur == '&')
	{
		if (nxt == '&' && prev != ' ')
			(*n_len)++;
		else if (prev == '&' && nxt != ' ')
			(*n_len)++;
	}
	else if (cur == '|')
	{
		if (nxt == '|' && prev != ' ')
			(*n_len)++;
		else if (prev == '|' && nxt != ' ')
			(*n_len)++;
	}
}
