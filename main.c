#include "main.h"

void sig_handler(int sig);
int execute(string *args, string *front);

alias *aliases;
string p_name;
int hist;

/**
 * main - simple shell
 * @argc: count of arguments
 * @argv: pointers to arguments
 *
 * Return: 0
 */
int main(int argc, string argv[])
{
	int r_value, ret_n;
	int *e_status = &ret_n;
	string pmt = "$ ", new_line = "\n";

	r_value = 0;
	p_name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*e_status = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		r_value = pfile_cmds(argv[1], e_status);
		free_env();
		free_alias_list(aliases);
		return (*e_status);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (r_value != _EOF && r_value != EXIT)
			r_value = handle_args(e_status);
		free_env();
		free_alias_list(aliases);
		return (*e_status);
	}

	while (1)
	{
		write(STDOUT_FILENO, pmt, 2);
		r_value = handle_args(e_status);
		if (r_value == _EOF || r_value == EXIT)
		{
			if (r_value == _EOF)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*e_status);
		}
	}
	free_env();
	free_alias_list(aliases);

	return (*e_status);
}

/**
 * sig_handler - prints a new prompt upon signal
 * @sig: signal number
 *
 * Return: void
 */
void sig_handler(int sig)
{
	string new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}
