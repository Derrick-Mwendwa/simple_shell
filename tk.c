#include "main.h"

string *_strtk(string ln, string dl);

/**
 * len_t - locates the first occurrence of any byte in a string
 * @s: string to be searched
 * @dl: delimiter character
 *
 * Return: delimiter marking the end
 */
int len_t(string s, string dl)
{
	int i, len;

	i = 0;
	len = 0;
	while (*(s + i) && *(s + i) != *dl)
	{
		len++;
		i++;
	}

	return (len);
}

/**
 * t_count - counts delimiters in a string
 * @s: string to be searched
 * @dl: delimiter character
 *
 * Return: no of words
 */
int t_count(string s, string dl)
{
	int i, tk, len;

	tk = 0;
	len = 0;
	for (i = 0; *(s + i); i++)
		len++;
	for (i = 0; i < len; i++)
	{
		if (*(s + i) != *dl)
		{
			tk++;
			i += len_t(s + i, dl);
		}
	}

	return (tk);
}

/**
 * _strtk - Tokenizes a string.
 * @ln: The string.
 * @dl: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
string *_strtk(string ln, string dl)
{
	int i, tk, t, ls, l;
	string *p;

	i = 0;
	tk = t_count(ln, dl);
	if (tk == 0)
		return (NULL);
	p = malloc(sizeof(string) * (tk + 2));
	if (!p)
		return (NULL);
	for (t = 0; t < tk; t++)
	{
		while (ln[i] == *dl)
			i++;
		ls = len_t(ln + i, dl);
		p[t] = malloc(sizeof(char) * (ls + 1));
		if (!p[t])
		{
			for (i -= 1; i >= 0; i--)
				free(p[i]);
			free(p);
			return (NULL);
		}
		for (l = 0; l < ls; l++)
		{
			p[t][l] = ln[i];
			i++;
		}
		p[t][l] = '\0';
	}
	p[t] = NULL;
	p[t + 1] = NULL;

	return (p);
}
