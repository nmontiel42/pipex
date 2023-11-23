/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:30:08 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/23 13:15:35 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	free_all_2(t_data *data);

int	new_split(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	env[i] += 5;
	data->env = new_split_version(env[i], ':');
	if (data->env == NULL)
		return (free_all(data), perror("Error del split"), EXIT_FAILURE);
	return (0);
}

void	free_all(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->env != NULL)
	{
		while (data->env[i] != NULL)
			free((data->env)[i++]);
		free(data->env);
	}
	i = -1;
	if (data->cmd != NULL)
	{
		while (data->cmd[++i] != NULL)
		{
			j = -1;
			while ((data->cmd)[i][++j] != NULL)
				free(data->cmd[i][j]);
			free((data->cmd)[i]);
		}
		free(data->cmd);
	}
	free_all_2(data);
	free(data);
}

static void	free_all_2(t_data *data)
{
	int	i;

	i = 0;
	if (data->path != NULL)
	{
		while (data->path[i] != NULL)
			free(data->path[i++]);
		free(data->path);
	}
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
