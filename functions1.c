#include "shell.h"

/**
 * child_pid - function that creates a child process.
 * @command: pointer to a command
 * @name: pointer to name.
 * @env: The pointer to the enviromental variables.
 * @loop: Number of executed cycles.
 * Return: Nothing.
 */
void child_pid(char **command, char *name, char **env, int loop)
{
	int pid = 0;
	int status = 0;
	int err = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		free_exit(command);
	}
	else if (pid == 0)
	{
		execute(command, name, env, loop);
		free_all(command);
	}
	else
	{
		err = waitpid(pid, &status, 0);
		if (err < 0)
		{
			free_exit(command);
		}
		free_all(command);
	}
}


/**
  * change_dir - function that changes working directory.
  * @path: pointer to working directory.
  * Return: 0 on success, -1 otherwise.
  */
int change_dir(const char *path)
{
	char *buf = NULL;
	size_t size = 1024;

	if (path == NULL)
		path = getcwd(buf, size);
	if (chdir(path) == -1)
	{
		perror(path);
		return (98);
	}
	return (1);
}

/**
 * execute - function that executes a command.
 * @command: pointer to a command
 * @name: pointer to the name.
 * @env: The pointer to the enviromental variables.
 * @loop: Number of executed cycles.
 * Return: Nothing.
 */
void execute(char **command, char *name, char **env, int loop)
{
	char **pathways = NULL, *full_path = NULL;
	struct stat st;
	unsigned int i = 0;

	if (_strcmp(command[0], "env") != 0)
		print_env(env);
	if (stat(command[0], &st) == 0)
	{
		if (execve(command[0], command, env) < 0)
		{
			perror(name);
			free_exit(command);
		}
	}
	else
	{
		pathways = _getPATH(env);
		while (pathways[i])
		{
			full_path = _strcat(pathways[i], command[0]);
			i++;
			if (stat(full_path, &st) == 0)
			{
				if (execve(full_path, command, env) < 0)
				{
					perror(name);
					free_all(pathways);
					free_exit(command);
				}
				return;
			}
		}
		msgerror(name, loop, command);
		free_all(pathways);
	}
}


/**
 * print_env - function that prints enviromental variables.
 * @env: The pointer to enviromental variables.
 */
void print_env(char **env)
{
	size_t i = 0, len = 0;

	while (env[i])
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}

}

/**
 * msgerror - A function that prints message not found.
 * @name: pointer to name.
 * @loop: Number of cycles.
 * @command: The pointer to command.
 */
void msgerror(char *name, int loop, char **command)
{
	char c;

	c = loop + '0';
	write(STDOUT_FILENO, name, _strlen(name));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &c, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, command[0], _strlen(command[0]));
	write(STDOUT_FILENO, ": not found\n", 12);
}
