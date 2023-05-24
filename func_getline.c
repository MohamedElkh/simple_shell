#include "shell.h"

void *_realloc(void *ptr, unsigned int old_value, unsigned int new_value);

void assign_lineptr(char **linptr, size_t *n, char *buff, size_t b);
ssize_t _getline(char **lptr, size_t *num, FILE *stream);

/**
 * _realloc - func to realoce a memory block using malloc and free.
 * @ptr: the memory previously allocated.
 * @old_value: The size in bytes
 * @new_value: The size in bytes
 *
 * Return: if new_size == old_size - ptr
 */
void *_realloc(void *ptr, unsigned int old_value, unsigned int new_value)
{
	void *mem;
	unsigned int i;
	char *ptr_cpy;
	char *fill;

	if (new_value == old_value)
	{
		return (ptr);
	}

	if (ptr == NULL)
	{
		mem = malloc(new_value);

		if (mem == NULL)
		{
			return (NULL);
		}

		return (mem);
	}

	if (new_value == 0 && ptr != NULL)
	{
		free(ptr);

		return (NULL);
	}

	ptr_cpy = ptr;

	mem = malloc(sizeof(*ptr_cpy) * new_value);
	if (mem == NULL)
	{
		free(ptr);

		return (NULL);
	}

	fill = mem;

	for (i = 0; i < old_value && i < new_value; i++)
	{
		fill[i] = *ptr_cpy++;
	}

	free(ptr);
	return (mem);
}

/**
 * assig_linptr - func to the lineptr variable for _getline.
 * @linptr: buffer to store an input string.
 * @n: size of lineptr.
 * @buff: string to assign to lineptr.
 * @b: size of buffer.
 */

void assig_linptr(char **linptr, size_t *n, char *buff, size_t b)
{
	if (*linptr == NULL)
	{
		if (b > 120)
		{
			*n = b;
		}
		else
		{
			*n = 120;
		}

		*linptr = buff;
	}
	else if (*n < b)
	{
		if (b > 120)
		{
			*n = b;
		}
		else
		{
			*n = 120;
		}

		*linptr = buff;
	}
	else
	{
		_strcpy(*linptr, buff);

		free(buff);
	}
}

/**
 * _getline - func to Reads input from a stream.
 * @lptr: abuffer to store the input.
 * @num: The size of lineptr.
 * @stream: the stream
 *
 * Return: number of bytes read.
 */

ssize_t _getline(char **lptr, size_t *num, FILE *stream)
{
	static ssize_t input;
	ssize_t rt;
	char c = 'x';
	char *buf;
	int i;

	if (input == 0)
	{
		fflush(stream);
	}
	else
	{
		return (-1);
	}

	input = 0;

	buf = malloc(sizeof(char) * 120);

	if (!buf)
	{
		return (-1);
	}

	while (c != '\n')
	{
		i = read(STDIN_FILENO, &c, 1);

		if (i == -1 || (i == 0 && input == 0))
		{
			free(buf);

			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
		{
			buf = _realloc(buf, input, input + 1);
		}

		buf[input] = c;
		input++;
	}

	buf[input] = '\0';

	assig_linptr(lptr, num, buf, input);

	rt = input;

	if (i != 0)
	{
		input = 0;
	}
	return (rt);
}
