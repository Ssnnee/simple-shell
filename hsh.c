#include "hsh.h"
/**
 * main - The main function of the shell program.
 * @argc: The number of arguments passed to the program.
 * @argv: An array of strings containing the arguments passed to the program.
 *
 * Return: The exit status of the shell program.
 */
int main(int argc, char **argv)
{
	app_name = argv[0];

	/* Suppress unused parameter warnings */
	(void)argc;
	(void)argv;

	/* Run the shell loop */
	return (shell_loop());
}
/**
 * _putchar - This function writes a character to stdout.
 * @c: The character to be written.
 *
 * Return: On success, the number of characters written.
 * On error, -1 is returned.
 */
int _putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
