#include "utils.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * main - entry point of program
 * @ac: number of command line args including the command itself
 * @av: the args passed to the commandline as a string
 * Return: returns 0 for success or > 0 for anything else
 */
int main(int ac, char **av)
{
    FILE *src = NULL;
    size_t file_contents = 0;
    char *contents = NULL;

    if (ac < 2)
    {
        printf("mouse: requires a source file to parse.\nexiting...\n");
        return 1;
    }
    if (!(src = fopen(av[1], "r")))
    {
        printf("mouse: file could not be opened.\nexiting...\n");
        return 1;
    }

    /* load the contents of the file into memory
     * - this has both advantages and disadvantages
     *   - advantage being it'll be easier to parse and tokenise
     *   - disadvantage being if the file is too big we use up too much mem
     */

    file_contents = load_file(src, &contents);

    fclose(src);
    free(contents);
    return 0;
}
