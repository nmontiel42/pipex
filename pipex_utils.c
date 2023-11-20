/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:53:27 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/20 16:10:19 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	new_split(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	env[i] += 5;
	data->env = ft_split (env[i], ':');
	if (data->env == NULL)
		return (free_all(data), perror("Error del split"), EXIT_FAILURE);
	return (0);
}

void	free_all(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->env != NULL)
		free((data->env)[i++]);
	free(data->env);
	i = 0;
	while (data->cmd != NULL)
	{
		j = 0;
		while ((data->cmd)[i][j])
			free((data->cmd)[i][j++]);
		free((data->cmd)[i]);
	}
	free(data->cmd);
	free(data);
}

int	ft_check(t_data *data, int len)
{
	data->i = -1;
	data->path = ft_calloc(len, sizeof(char *));
	if (!data->path)
		free(data->path);
	while (data->cmd[++data->i] != NULL)
	{
		data->j = -1;
		while (data->env[++data->j] != NULL)
		{
			data->temp = ft_strjoin(data->env[data->j], "/");
			data->temp_path = ft_strjoin(data->temp, data->cmd[data->i][0]);
			if (data->temp == NULL || data->temp_path == NULL)
				exit(EXIT_FAILURE);
			free(data->temp);
			if (access(data->temp_path, F_OK) == 0
				&& access(data->temp_path, X_OK) == 0)
			{
				data->path[data->i] = data->temp_path;
				data->temp_path = NULL;
				break ;
			}
			free(data->temp_path);
		}
	}
	return (EXIT_SUCCESS);
}

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_exec(t_data *data)
{
	int		end[2];
	pid_t	child_pid;

	if (pipe(end) == -1)
		ft_error("Fallo de pipe");
	child_pid = fork();
	if (child_pid == -1)
		ft_error("Fallo de child_pid");
	if (child_pid == 0)
		child_process(end, data);
	else
	{
		close(end[0]);
		if (dup2(data->file1, STDIN_FILENO) == -1)
			ft_error("Fallo de stdin");
		if (dup2(end[1], STDOUT_FILENO) == -1)
			ft_error("Fallo de stdout");
		close(data->file1);
		if (execve(data->path[0], data->cmd[0], NULL) == -1)
			ft_error("Fallo de execve");
		waitpid(child_pid, NULL, 0);
	}
}
