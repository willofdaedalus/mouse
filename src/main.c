#include "utils.h"
#include "environment.h"
#include "interpreter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t load_file(FILE *src, char **buffer);

/**
 * entry point of program
 *
 * @ac: number of command line args including the command itself
 * @av: the args passed to the commandline as a string
 * Return: returns 0 for success or > 0 for anything else
 */
int main(int ac, char **av)
{
    FILE *src = NULL;
    size_t file_contents = 0;
    char *contents = NULL;
    environment *global_env = NULL;

    if (ac < 2)
    {
        printf("mouse: requires a source file to parse.\nexiting...\n");
        return 1;
    }
    if ((src = fopen(av[1], "r")) == NULL)
    {
        printf("mouse: file could not be opened.\nexiting...\n");
        return 1;
    }

    /* load the contents of the file into memory
     * - this has both advantages and disadvantages
     *   - advantage being it'll be easier to parse and tokenise
     *   - disadvantage being if the file is too big we use up too much mem
     */

    global_env = init_env();

    file_contents = load_file(src, &contents);
    begin_interpreter(contents, file_contents, global_env);

    fclose(src);
    free_env(global_env);
    free(contents);
    return 0;
}

/**
 * this loads the file passed into memory
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
