/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:32:53 by snakita           #+#    #+#             */
/*   Updated: 2021/12/13 21:32:55 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	*mypath(char **cmd, char **env)
{
	char	**path;
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	if (cmd[0][0] == '/')
		return (cmd[0]);
	while (env[++i])
		if ((ft_strncmp(env[i], "PATH=", 5)) == 0)
			path = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		str = ft_strjoin(tmp, cmd[0]);
		if (!(access(str, F_OK)))
			return (str);
		free(str);
	}
	return (NULL);
}

static void	gnl(int *end, char *finish)
{
	char	*line;

	close(end[0]);
	ft_putstr_fd("pipe heredoc> ", 1);
	while (get_next_line(&line))
	{
		if ((ft_strncmp(finish, line, ft_strlen(finish))) == 0)
			exit(EXIT_FAILURE);
		ft_putstr_fd("pipe heredoc> ", 1);
		if (write(end[1], line, ft_strlen(line)) == -1)
			ft_error("pipex: write error: ");
	}
	ft_error("pipex: write here_doc error: ");
}

void	ft_here_doc(char *finish, int argc)
{
	int	end[2];
	int	pid;

	if (argc < 6)
	{
		ft_putstr_fd("pipex: error: wrong count of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(end) == -1)
		ft_error("pipex: error when creating the pipe: ");
	pid = fork();
	if (pid == -1)
		ft_error("pipex: error when forking: ");
	if (pid == 0)
		gnl(end, finish);
	else
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			ft_error("pipex: dup2 error: ");
		waitpid(pid, NULL, 0);
	}
}

int	get_next_line(char **line)
{
	char	*buffer;
	char	join;
	int		i;
	int		bytes_buf;

	i = 0;
	bytes_buf = 0;
	buffer = (char *) malloc(10000);
	if (!buffer)
		return (-1);
	bytes_buf = read(0, &join, 1);
	while (bytes_buf && join != '\n' && join != '\0')
	{
		if (join != '\n' && join != '\0')
			buffer[i] = join;
		i++;
		bytes_buf = read(0, &join, 1);
	}
	buffer[i++] = '\n';
	buffer[i] = '\0';
	*line = buffer;
	free(buffer);
	return (bytes_buf);
}
