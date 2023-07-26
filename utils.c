#include "shell.h"

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: Difference between the two strings
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _atoi - Convert a string to an integer
 * @str: The string to convert
 *
 * Return: The converted integer
 */
int _atoi(const char *str)
{
	int result = 0;
	int sign = 1;

	while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;

	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}

	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	return (result * sign);
}

/**
 * _strlen - Calculate the length of a string
 * @s: The string to measure
 *
 * Return: The length of the string
 */
size_t _strlen(const char *s)
{
	size_t len = 0;

	while (s[len])
		len++;

	return len;
}
