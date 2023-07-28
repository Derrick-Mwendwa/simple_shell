#include "main.h"

/**
 * h_env - shows information about the shellby builtin command 'env'
 *
 * Return: void
 */
void h_env(void)
{
	string message = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * h_setenv - shows information about the shellby builtin command 'setenv'
 *
 * Return: void
 */
void h_setenv(void)
{
	string message = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * h_unsetenv - shows information about the shellby builtin command 'unsetenv'
 *
 * Return: void
 */
void h_unsetenv(void)
{
	string message = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "message to stderr.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}
