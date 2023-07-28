#include "main.h"

extern alias *aliases;

void set_alias(string name, string val);
void print(alias *x);

/**
 * _alias - prints a list of all aliases, or sets an alias
 * @args: pointer to array of arguments
 * @f: pointer to the first element of args
 *
 * Return: 0 on success, 1 on failure
 */
int _alias(string *args, char __attribute__((__unused__)) **f)
{
	int i, r_value;
	string value;
	alias *t;

	t = aliases;
	r_value = 0;

	if (!args[0])
	{
		while (t)
		{
			print(t);
			t = t->next;
		}
		return (r_value);
	}

	for (i = 0; args[i]; i++)
	{
		t = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (t)
			{
				if (_strcmp(args[i], t->name) == 0)
				{
					print(t);
					break;
				}
				t = t->next;
			}
			if (!t)
			{
				r_value = create_err(args + i, 1);
			}
		}
		else
		{
			set_alias(args[i], value);
		}
	}

	return (r_value);
}

/**
 * set_alias - sets an alias
 * @name: name of the alias
 * @val: value of the alias
 *
 * Return: void
 */
void set_alias(string name, string val)
{
	int i, j, len;
	string n_val;
	alias *t;

	t = aliases;

	*val = '\0';
	val++;
	len = _strlen(val) - _strspn(val, "'\"");
	n_val = malloc((len + 1) * sizeof(char));

	if (!n_val)
		return;

	for (i = 0, j = 0; val[i]; i++)
	{
		if (val[i] != '\'' && val[i] != '"')
			n_val[j++] = val[i];
	}

	n_val[j] = '\0';

	while (t)
	{
		if (_strcmp(name, t->name) == 0)
		{
			free(t->val);
			t->val = n_val;
			break;
		}
		t = t->next;
	}

	if (!t)
		add_alias_e(&aliases, name, n_val);
}

/**
 * print - prints alias in format: "name='value'\n"
 * @x: pointer to alias
 *
 * Return: void
 */
void print(alias *x)
{
	int len;
	string alias;

	len = 4 + _strlen(x->name) + _strlen(x->val);
	alias = malloc((len + 1) * sizeof(char));

	if (!alias)
		return;

	_strcpy(alias, x->name);
	_strcat(alias, "='");
	_strcat(alias, x->val);
	_strcat(alias, "'\n");

	write(STDOUT_FILENO, alias, len);

	free(alias);
}
