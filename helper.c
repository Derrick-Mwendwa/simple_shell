#include "main.h"

void var_repl(string *ln, int *e_status);

/**
 * free_args - frees the args array
 * @args: pointer to the args array
 * @f: pointer to the front array
 */
void free_args(string *args, string *f)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(f);
}

/**
 * var_repl - variable replacement
 * @ln: pointer to the line
 * @e_status: pointer to the exit status
 *
 * Return: void
 */
void var_repl(string *ln, int *e_status)
{
	int i, j, len;
	string repl, o_ln, n_ln;

	j = 0;
	repl = NULL;
	o_ln = *ln;

	for (i = 0; o_ln[i]; i++)
	{
		if (o_ln[i] == '$' && o_ln[i + 1] &&
			o_ln[i + 1] != ' ')
		{
			if (o_ln[i + 1] == '$')
			{
				repl = get_pid();
				j = i + 2;
			}
			else if (o_ln[i + 1] == '?')
			{
				repl = _itoa(*e_status);
				j = i + 2;
			}
			else if (o_ln[i + 1])
			{
				for (j = i + 1; o_ln[j] &&
								o_ln[j] != '$' &&
								o_ln[j] != ' ';
					 j++)
					;
				len = j - (i + 1);
				repl = get_env_val(&o_ln[i + 1], len);
			}
			n_ln = malloc(i + _strlen(repl) + _strlen(&o_ln[j]) + 1);
			if (!ln)
				return;
			n_ln[0] = '\0';
			_strncat(n_ln, o_ln, i);
			if (repl)
			{
				_strcat(n_ln, repl);
				free(repl);
				repl = NULL;
			}
			_strcat(n_ln, &o_ln[j]);
			free(o_ln);
			*ln = n_ln;
			o_ln = n_ln;
			i = -1;
		}
	}
}
