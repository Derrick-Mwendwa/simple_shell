#include "main.h"

list_t *get_path_dir(string path);

/**
 * get_location - locates a command in PATH
 * @cmd: command to locate
 *
 * Return: pathname of command or NULL if not found
 */
string get_location(string cmd)
{
	string *path, temp;
	list_t *dirs, *head;
	struct stat x;

	path = get_env("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(cmd) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, cmd);

		if (stat(temp, &x) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}
	free_list(head);

	return (NULL);
}

/**
 * rpl_path_dir - replaces any leading/sandwiched/trailing colons
 * @path: list of directories
 *
 * Return: copy of path with any leading/sandwiched/trailing colons
 */
string rpl_path_dir(string path)
{
	int i, len;
	string path_cp, pwd;

	len = 0;
	pwd = *(get_env("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_cp = malloc(sizeof(char) * (len + 1));
	if (!path_cp)
		return (NULL);
	path_cp[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_cp, pwd);
				_strcat(path_cp, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_cp, ":");
				_strcat(path_cp, pwd);
			}
			else
				_strcat(path_cp, ":");
		}
		else
		{
			_strncat(path_cp, &path[i], 1);
		}
	}
	return (path_cp);
}

/**
 * get_path_dir - creates a linked list of directories in PATH
 * @path: list of directories
 *
 * Return: pointer to head of linked list
 */
list_t *get_path_dir(string path)
{
	int i;
	string *dirs, path_cp;
	list_t *head;

	head = NULL;
	path_cp = rpl_path_dir(path);

	if (!path_cp)
		return (NULL);
	dirs = _strtk(path_cp, ":");
	free(path_cp);
	if (!dirs)
		return (NULL);
	for (i = 0; dirs[i]; i++)
	{
		if (add_node_e(&head, dirs[i]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}
	free(dirs);

	return (head);
}
