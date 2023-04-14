#include "main.h"

/**
 * append_text_to_file - Appends text at the end of a file
 *
 * @filename: Name of the file to append to
 * @text_content: Text to append to the file
 *
 * Return: 1 on success, -1 on failure
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int fd, num_written = 0, text_len = 0;

	if (filename == NULL)
		return (-1);

	if (text_content != NULL)
	{
		while (text_content[text_len] != '\0')
			text_len++;
	}

	fd = open(filename, O_WRONLY | O_APPEND);

	if (fd == -1)
		return (-1);

	if (text_len > 0)
	{
		num_written = write(fd, text_content, text_len);

		if (num_written == -1)
			return (-1);
	}

	close(fd);

	return (1);
}
