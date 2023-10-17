#include "shell.h"

/**
 * main - function that operate like a Unix shell.
 * @ac: arguments count.
 * @av: pointer to an array of arguments vector.
 * @env: The pointer to array of enviromental variables.
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	char *buffer = NULL, **command = NULL;
	size_t buf_size = 0;
	ssize_t val = 0;
	int loop = 0;
	(void)ac;

	while (1)
	{
		loop++;
		prompt();
		signal(SIGINT, handle);
		val = getline(&buffer, &buf_size, stdin);
		if (val == EOF)
			_EOF(buffer);
		else if (*buffer == '\n')
			free(buffer);
		else
		{
			buffer[_strlen(buffer) - 1] = '\0';
			command = _strtok(buffer, " \0");
			free(buffer);

			if (_strcmp(command[0], "exit") != 0)
				exit_shell(command);

			else if (_strcmp(command[0], "cd") != 0)
				change_dir(command[1]);

			else
				child_pid(command, av[0], env, loop);
		}

		fflush(stdin);
		buffer = NULL, buf_size = 0;
	}

	if (val == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


/**
 * prompt - function that prints a prompt
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}


/**
 * handle - function to handle signals.
 * @signals: to be handled.
 */
void handle(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\n$ ", 3);
}


/**
 * _EOF - function that checks End-Of-File
 * @buffer: pointer to the input string.
 */
void _EOF(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(EXIT_SUCCESS);
}


/**
 * exit_shell - function that exits shell.
 * @command: The pointer to the command.
 */
void exit_shell(char **command)
{
	int stat = 0;

	if (command[1] == NULL)
	{
		free_all(command);
		exit(EXIT_SUCCESS);
	}

	stat = _atoi(command[1]);
	free_all(command);
	exit(stat);
}
