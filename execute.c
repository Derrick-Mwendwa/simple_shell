#include "main.h"

extern alias *aliases;

int execute(string *args, string *f);

/**
 * execute - executes a command
 * @args: arguments to execute
 * @f: pointer to the front of the args
 *
 * Return: exit status
 */
int execute(string *args, string *f)
{
	int status, fg = 0, r_value = 0;
	string cmd = args[0];
	pid_t c_pid;

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		fg = 1;
		cmd = get_location(cmd);
	}
	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			r_value = (create_err(args, 126));
		else
			r_value = (create_err(args, 127));
	}
	else
	{
		c_pid = fork();
		if (c_pid == -1)
		{
			if (fg)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (c_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				r_value = (create_err(args, 126));
			free_env();
			free_args(args, f);
			free_alias_list(aliases);
			_exit(r_value);
		}
		else
		{
			wait(&status);
			r_value = WEXITSTATUS(status);
		}
	}
	if (fg)
		free(cmd);

	return (r_value);
}
