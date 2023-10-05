#include "shell.h"

/**
 * cStringToInt - converts a string to an integer
 * @string: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int cStringToInt(char *string)
{
	int index = 0;
	unsigned long int result = 0;

	if (*string == '+')
		string++;  
	for (index = 0;  string[index] != '\0'; index++)
	{
		if (string[index] >= '0' && string[index] <= '9')
		{
			result *= 10;
			result += (string[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * pCE - prints an error message
 * @inf: the parameter & return info struct
 * @eStr: string containing specified error type
 */
void pCE(info_t *inf, char *eStr)
{
	_customPuts(inf->fname);
	_customPuts(": ");
	printCustomInt(inf->line_count, STDERR_FILENO);
	_customPuts(": ");
	_customPuts(inf->argv[0]);
	_customPuts(": ");
	_customPuts(eStr);
}

/**
 * pCI - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @filedescriptor: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int pCI(int input, int filedescriptor)
{
	int (*customPutsChar)(char) = _customPuts;
	int i, count = 0;
	unsigned int absoluteValue, current;

	if (filedescriptor == STDERR_FILENO)
		customPutsChar = _customPuts;
	if (input < 0)
	{
		absoluteValue = -input;
		customPutsChar('-');
		count++;
	}
	else
		absoluteValue = input;
	current = absoluteValue;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absoluteValue / i)
		{
			customPutsChar('0' + current / i);
			count++;
		}
		current %= i;
	}
	customPutsChar('0' + current);
	count++;

	return (count);
}

/**
 * cCNumber - converter function, a clone of itoa
 * @number: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *cCNumber(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rCC - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 */
void rCC(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
