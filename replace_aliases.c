#include "main.h"

extern alias *aliases;

/**
 * replace_aliases - replaces aliases with their values
 * @args: pointer to array of arguments
 *
 * Return: pointer to array of arguments with aliases replaced
 */
string *replace_aliases(string *args)
{
	int i;
	alias *t;
	string val;

	if (_strcmp(args[0], "alias") == 0)
		return (args);

	for (i = 0; args[i]; i++)
	{
		t = aliases;
		while (t)
		{
			if (_strcmp(args[i], t->name) == 0)
			{
				val = malloc(sizeof(char) * (_strlen(t->val) + 1));

				if (!val)
				{
					free_args(args, args);
					return (NULL);
				}

				_strcpy(val, t->val);
				free(args[i]);
				args[i] = val;
				--i;
				break;
			}

			t = t->next;
		}
	}

	return (args);
}
