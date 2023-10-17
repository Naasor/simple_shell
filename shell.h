#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int ac, char **av, char **env);
void prompt(void);
void handle(int signals);
void _EOF(char *buffer);
void exit_shell(char **command);

void child_pid(char **command, char *name, char **env, int loop);
int change_dir(const char *path);
void execute(char **command, char *name, char **env, int loop);
void print_env(char **env);
void msgerror(char *name, int loop, char **command);

void free_all(char **command);
void free_exit(char **command);
char **_getPATH(char **env);
char **_strtok(char *buffer, const char *s);


int _atoi(char *s);
unsigned int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);


#endif
