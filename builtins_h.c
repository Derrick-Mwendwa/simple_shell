#include "main.h"

/**
 * h_all - shows information about all builtin commands
 *
 * Return: void
 */
void h_all(void)
{
	string message = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * h_alias - shows information about the shellby builtin command 'alias'
 *
 * Return: void
 */
void h_alias(void)
{
	string message = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * h_cd - shows information about the shellby builtin command 'cd'
 *
 * Return: void
 */
void h_cd(void)
{
	string message = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, message, _strlen(message));
	message = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "after a change of directory.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * h_exit - shows information about the shellby builtin command 'exit'
 *
 * Return: void
 */
void h_exit(void)
{
	string message = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " exit 0.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * h_help - shows information about the shellby builtin command 'help'
 *
 * Return: void
 */
void h_help(void)
{
	string message = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "builtin command.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}
