/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:53:27 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/17 13:14:49 by nmontiel         ###   ########.fr       */
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
		return (free(data->env), perror("Error del split"), EXIT_FAILURE);
	return (0);
}
