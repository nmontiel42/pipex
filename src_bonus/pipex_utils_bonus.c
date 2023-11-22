/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:30:08 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/22 14:36:39 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	ft_error2(char *str, int here_doc)
{
	if (here_doc)
		unlink("here_doc.tmp");
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_exec2(t_data *data, int argc, char **argv)
{
	int		end[2];
	pid_t	child_pid;

	check_flag(argc, argv, data);
	if (dup2(data->file1, STDIN_FILENO) == -1)
		ft_error2("Error de stdin file1", data->flag_hd);
	data->i = -1;
	while (data->cmd[++data->i] != NULL)
	{
		if (pipe(end) == -1)
			ft_error2("Fallo de pipe", data->flag_hd);
		child_pid = fork();
		if (child_pid == -1)
			ft_error2("Fallo de child_pid", data->flag_hd);
		if (child_pid == 0)
		{
			if (data->cmd[data->i + 1] == NULL)
			{
				dup2(data->file2, STDOUT_FILENO);
				if (execve(data->path[data->i], data->cmd[data->i], NULL) == -1)
					ft_error2("Error de execve child", data->flag_hd);
				break ;
			}
			child_process(end, data);
		}
		else
		{
			waitpid(child_pid, NULL, 0);
			close(end[1]);
			if (dup2(end[0], STDIN_FILENO) == -1)
				ft_error2("Error de padre dup2", data->flag_hd);
		}
	}
}
