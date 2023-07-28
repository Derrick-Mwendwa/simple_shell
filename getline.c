#include "main.h"

void *_realloc(void *p, unsigned int o_size, unsigned int n_size);
void assign_lnptr(string *l_ptr, size_t *n, string buff, size_t b);

/**
 * _getline - reads an entire line from stream
 * @l_ptr: A buffer to store the input
 * @n: size of the buffer
 * @stream: stream to read from
 *
 * Return: no of bytes read, -1 upon failure
 */
ssize_t _getline(string *l_ptr, size_t *n, FILE *stream)
{
	int i;
	char c;
	string buff;
	static ssize_t inp;
	ssize_t ret_v;

	c = 'x';

	if (inp == 0)
		fflush(stream);
	else
		return (-1);
	inp = 0;

	buff = malloc(120 * sizeof(char));
	if (!buff)
		return (-1);

	while (c != '\n')
	{
		i = read(STDIN_FILENO, &c, 1);
		if (i == -1 || (i == 0 && inp == 0))
		{
			free(buff);
			return (-1);
		}
		if (i == 0 && inp != 0)
		{
			inp++;
			break;
		}

		if (inp >= 120)
			buff = _realloc(buff, inp, inp + 1);

		buff[inp] = c;
		inp++;
	}
	buff[inp] = '\0';
	assign_lnptr(l_ptr, n, buff, inp);
	ret_v = inp;

	if (i != 0)
		inp = 0;

	return (ret_v);
}

/**
 * _realloc - reallocates a memory block
 * @p: pointer to the memory previously allocated
 * @o_size: size in bytes of the allocated space for p
 * @n_size: size in bytes for the new memory block
 *
 * Return: pointer to the allocated memory, NULL upon failure
 */
void *_realloc(void *p, unsigned int o_size, unsigned int n_size)
{
	unsigned int i;
	string p_cp, f;
	void *memory;

	if (n_size == o_size)
		return (p);

	if (p == NULL)
	{
		memory = malloc(n_size);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (n_size == 0 && p != NULL)
	{
		free(p);
		return (NULL);
	}

	p_cp = p;
	memory = malloc(sizeof(*p_cp) * n_size);
	if (memory == NULL)
	{
		free(p);
		return (NULL);
	}

	f = memory;

	for (i = 0; i < o_size && i < n_size; i++)
		f[i] = *p_cp++;

	free(p);

	return (memory);
}

/**
 * assign_lnptr - reallocates memory for lineptr if needed
 * @l_ptr: pointer to the buffer to store the read line
 * @n: size of the buffer
 * @buff: string to store in lnptr
 * @b: size of buffer
 *
 * Return: void
 */
void assign_lnptr(string *l_ptr, size_t *n, string buff, size_t b)
{
	if (*l_ptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*l_ptr = buff;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*l_ptr = buff;
	}
	else
	{
		_strcpy(*l_ptr, buff);
		free(buff);
	}
}
