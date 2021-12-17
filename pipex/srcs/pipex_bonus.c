/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:39:13 by snakita           #+#    #+#             */
/*   Updated: 2021/12/13 21:39:16 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_open(char *arg, int index)
{
	int	fd;

	if (index == 0)
		fd = open(arg, O_RDONLY);
	if (index == 1)
		fd = open(arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (index == 2)
		fd = open(arg, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(arg);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_execve(char *ar, char **env)
{
	char	**cmd1;

	cmd1 = ft_split(ar, ' ');
	if (execve(mypath(cmd1, env), cmd1, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(ar, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

static void	child_process(char *ar, char **env)
{
	int		end[2];
	pid_t	pid;

	if (pipe(end) == -1)
		ft_error("pipe");
	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) == -1)
			ft_error("dup2");
		close(end[1]);
		ft_execve(ar, env);
	}
	else
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			ft_error("dup2");
		close(end[0]);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	fd[2];

	if (argc >= 5)
	{
		if ((ft_strncmp(argv[1], "here_doc", 8)) == 0)
		{
			i = 3;
			ft_here_doc(argv[2], argc);
			fd[1] = ft_open(argv[argc - 1], 2);
		}
		else
		{
			i = 2;
			fd[0] = ft_open(argv[1], 0);
			fd[1] = ft_open(argv[argc - 1], 1);
			dup2(fd[0], STDIN_FILENO);
		}
		while (i < argc -2)
			child_process(argv[i++], env);
		dup2(fd[1], STDOUT_FILENO);
		ft_execve(argv[argc - 2], env);
	}
	ft_putstr_fd("pipex: error: wrong count of arguments\n", 2);
	exit(EXIT_SUCCESS);
}
