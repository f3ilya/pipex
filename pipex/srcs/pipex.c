/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:36:34 by snakita           #+#    #+#             */
/*   Updated: 2021/12/02 20:36:36 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	child_one(char **argv, char **env, int *end)
{
	int		f1;
	char	**cmd1;

	f1 = open(argv[1], O_RDONLY);
	if (f1 < 0)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
	dup2(f1, STDIN_FILENO);
	cmd1 = ft_split(argv[2], ' ');
	if (execve(mypath(cmd1, env), cmd1, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

static void	child_two(char **argv, char **env, int *end)
{
	int		f2;
	char	**cmd2;

	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 < 0)
	{
		perror(argv[4]);
		exit(EXIT_FAILURE);
	}
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	dup2(f2, STDOUT_FILENO);
	cmd2 = ft_split(argv[3], ' ');
	if (execve(mypath(cmd2, env), cmd2, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(argv[3], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

static void	pipex(char **argv, char **env, int *end, pid_t child[])
{
	if (pipe(end) == -1)
	{
		perror("pipex: Pipe");
		exit(EXIT_FAILURE);
	}
	child[0] = fork();
	if (child[0] < 0)
	{
		perror("pipex: Fork");
		exit(EXIT_FAILURE);
	}
	if (child[0] == 0)
		child_one(argv, env, end);
	child[1] = fork();
	if (child[1] < 0)
	{
		perror("pipex: Fork");
		exit(EXIT_FAILURE);
	}
	if (child[1] == 0)
		child_two(argv, env, end);
}

int	main(int argc, char **argv, char **env)
{
	int		end[2];
	int		status;
	pid_t	child[2];

	if (argc != 5)
	{
		ft_putstr_fd("pipex: inter: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	pipex(argv, env, end, child);
	close(end[0]);
	close(end[1]);
	waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
