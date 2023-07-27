#include "shell.h"
/**
 * _strcmp - function compares strings if match
 * @strng1: The first string arg
 * @strng2: The second string arg
 * Return: 0 for success
 */
int _strcmp(char *strng1, char *strng2)
{
	while ((*strng1 != '\0' && *strng2 != '\0') && *strng1 == *strng2)
	{
		strng1++;
		strng2++;
	}
	if (*strng1 == *strng2)
	{
		return (0);
	}
	else
	{
		return (*strng1 - *strng2);
	}
}

/**
 * _strdup - The function to duplicate string
 * @str: The string input
 * Return: buffer to dup string
 */
char *_strdup(char *str)
{
	char *dup = NULL;
	int i;
	int k = 0;

	if (str == NULL)
		return (NULL);
	for (k = 0; str[k] != '\0'; k++)
		;
	dup = malloc(4096);
	buffers5(dup);
	if (dup == NULL)
		return (NULL);
	for (i = 0; i <= k; i++)
		dup[i] = str[i];
	return (dup);
}

/**
 * _strlen - function finds the length of a string
 * @s: The char pointer
 * Return: length of string
 */
int _strlen(char *s)
{
	int i;

	i = 0;
	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}
