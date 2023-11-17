/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:53:27 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/17 15:03:33 by nmontiel         ###   ########.fr       */
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
		return (free_all(data->env), perror("Error del split"), EXIT_FAILURE);
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
