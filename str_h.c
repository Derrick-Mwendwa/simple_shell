#include "main.h"

/**
 * _strlen - gets the length of a string
 * @s: pointer to character string
 *
 * Return: length of string
 */
int _strlen(const string s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len]; len++)
		;

	return (len);
}

/**
 * _strcpy - copies a string pointed by src to dest
 * @dest: pointer to destination string
 * @src: pointer to source string
 *
 * Return: pointer to destination string
 */
string _strcpy(string dest, const string src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}

/**
 * _strcat - concats two strings
 * @dest: pointer to destination string
 * @src: pointer to source string
 *
 * Return: pointer to destination string
 */
string _strcat(string dest, const string src)
{
	string d_temp;
	string s_temp;

	d_temp = dest;
	s_temp =  src;
	while (*d_temp != '\0')
		d_temp++;

	while (*s_temp != '\0')
		*d_temp++ = *s_temp++;
	*d_temp = '\0';

	return (dest);
}

/**
 * _strncat - concats two strings with n bytes from src
 * @dest: pointer to destination string
 * @src: pointer to source string
 * @n: no of bytes from src
 *
 * Return: pointer to destination string
 */
string _strncat(string dest, const string src, size_t n)
{
	size_t i;
	size_t d_len = _strlen(dest);

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[d_len + i] = src[i];
	dest[d_len + i] = '\0';

	return (dest);
}
