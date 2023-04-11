#include "main.h"

/**
 * binary_to_uint - Converts a binary number to an unsigned int.
 * @b: A string of 0 and 1 characters.
 *
 * Return: The converted number, or 0 if there is one or more chars in
 *         the string b that is not 0 or 1 or b is NULL.
 */
unsigned int binary_to_uint(const char *b)
{
	unsigned int uint = 0;

	if (b == NULL)
		return (0);

	while (*b != '\0')
	{
		if (*b != '0' && *b != '1')
			return (0);

		uint <<= 1;
		if (*b == '1')
			uint += 1;

		b++;
	}

	return (uint);
}
