#include "utils.h"

#include <stdlib.h>
#include <string.h>


/**
 * load_file - this loads the file passed into memory
 *
 * @src: the file from whose contents we load into memory
 * @buffer: this is a pointer to a char pointer that holds
 * the actual contents into memory and passes it to a variable
 *
 * Return: the number of bytes read into memory
 */
size_t load_file(FILE *src, char **buffer)
{
	char *buf = NULL;
    long file_size = 0;

	/* go the end of the src */
	fseek(src, 0, SEEK_END);
	/* get the position of the pointer in the src
	 * which is in the case the end
	 */
	file_size = ftell(src);
	/* go back to the beginning of the src */
	rewind(src);

	buf = malloc(sizeof(char) * file_size + 1);
	if (!buf)
	{
		fprintf(stderr, "Malloc failed in load_file\n");
		exit(EXIT_FAILURE);
	}

	/* read into the buffer from the start to the end of the src */
	fread(buf, file_size, 1, src);

	buf[file_size] = '\0';

	*buffer = strdup(buf);

	free(buf);
	return file_size;
}

bool is_variable(char c)
{
    return c >= 'A' && c <= 'Z';
}

bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}
