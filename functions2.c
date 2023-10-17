#include "shell.h"


/**
 * free_all - A function that frees all the memory allocated for command.
 * @command: The pointer to allocated memory to free.
 * Return: Nothing.
 */
void free_all(char **command)
{
	size_t i = 0;

	if (command == NULL)
		return;

	while (command[i])
	{
		free(command[i]);
		i++;
	}

	if (command[i] == NULL)
		free(command[i]);
	free(command);
}


/**
 * free_exit - function that frees all the memory allocated then exit.
 * @command: pointer to allocated command memory to free.
 */
void free_exit(char **command)
{
	size_t i = 0;

	if (command == NULL)
		return;

	while (command[i])
	{
		free(command[i]);
		i++;
	}

	if (command[i] == NULL)
		free(command[i]);
	free(command);
	exit(EXIT_FAILURE);
}

/**
 * _getPATH - function to gets enviromental variable PATH.
 * @env: pointer to enviromental variables.
 * Return: pathways for commands.
 */
char **_getPATH(char **env)
{
	char *pathvalue = NULL, **pathways = NULL;
	unsigned int i = 0;

	pathvalue = strtok(env[i], "=");
	while (env[i])
	{
		if (_strcmp(pathvalue, "PATH"))
		{
			pathvalue = strtok(NULL, "\n");
			pathways = _strtok(pathvalue, ":");
			return (pathways);
		}
		i++;
		pathvalue = strtok(env[i], "=");
	}
	return (NULL);
}

/**
 * _strtok - function that split a string.
 * @s: a delimiter.
 * @buffer: The pointer to input string.
 * Return: string with full command.
 */
char **_strtok(char *buffer, const char *s)
{
	char *token = NULL, **command = NULL;
	size_t bufsize = 0;
	int i = 0;

	if (buffer == NULL)
		return (NULL);

	bufsize = _strlen(buffer);
	command = malloc((bufsize + 1) * sizeof(char *));
	if (command == NULL)
	{
		perror("Unable to allocate buffer");
		free(buffer);
		free_all(command);
		exit(EXIT_FAILURE);
	}

	token = strtok(buffer, s);
	while (token != NULL)
	{
		command[i] = malloc(_strlen(token) + 1);
		if (command[i] == NULL)
		{
			perror("Unable to allocate buffer");
			free_all(command);
			return (NULL);
		}
		_strcpy(command[i], token);
		token = strtok(NULL, s);
		i++;
	}
	command[i] = NULL;
	return (command);
}
