#include "main.h"

/**
 * _strchr - gets the first occurence of a character in a string
 * @s: string to be searched
 * @c: character to be searched for
 *
 * Return: pointer to first occurence of c in s, otherwise NULL
 */
string _strchr(string s, char c)
{
	int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == c)
			return (s + i);
	}

	return (NULL);
}

/**
 * _strspn - gets the length of a prefix substring
 * @s: string to be searched
 * @prf: prefix substring
 *
 * Return: number of bytes in the initial segment of s
 */
int _strspn(string s, string prf)
{
	int n_bytes;
	int i;

	n_bytes = 0;
	while (*s)
	{
		for (i = 0; prf[i]; i++)
		{
			if (*s == prf[i])
			{
				n_bytes++;
				break;
			}
		}
		s++;
	}

	return (n_bytes);
}

/**
 * _strcmp - compares two strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 *
 * Return: positive diff if s1 > s2
 *         0 if s1 = s2
 *         negative diff if s1 < s2
 */
int _strcmp(string s1, string s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - compares two strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 * @n: number of bytes to be compared
 *
 * Return: less than 0 if s1 < s2
 *         0 if s1 = s2 match
 *         greater than 0 if s1 > s2
 */
int _strncmp(const string s1, const string s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}

	if (i == n)
		return (0);
	else
		return (-15);
}
