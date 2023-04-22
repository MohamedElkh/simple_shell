#include "shell.h"

/**
 * p_number - function to print unsigned int 
 * @num: the character to be checked
 *
 * Return: nothing
 */

void p_number(size_t num)
{
	size_t i = num;

	if ((i / 10) > 0)
	{
		p_number(i / 10);
	}
	_putchar(i % 10 + '0');
}

/**
 * p_num - print number of putchar
 * @num: the character to be checked.
 *
 * Return: void
 */

void p_num(int num)
{
	size_t i = num;

	if (num < 0)
	{
		_putchar('-');
		i = -i;
	}
	if ((i / 10) > 0)
	{
		p_number(i / 10);
	}
	_putchar(i % 10 + '0');
}
