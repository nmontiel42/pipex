/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:23:33 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/23 13:11:39 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		file1;
	int		file2;
	char	**env;
	char	***cmd;
	char	**path;
	char	*temp;
	char	*temp_path;
	int		i;
	int		j;
	int		flag_hd;
	char	*line;
	int		fd;
}				t_data;

void		start_program(t_data *data);
void		child_process(int *fd, t_data *data);
int			obtain_comands(int argc, char **argv, t_data *data);
int			main(int argc, char **argv, char **env);
int			new_split(t_data *data, char **env);
void		free_all(t_data *data);
int			ft_check(t_data *data, int len);
void		ft_error(char *str);
void		ft_exec(t_data *data);
void		free_split(char **arr);
void		split_iterator(char **str, char d, char *aux, int *flag);
size_t		wordscount(char *str, char d);
int			wordlen(char *str, char d, int flag, char c);
char		**new_split_version(char *s, char d);

//BONUS
void		ft_error2(char *str, int here_doc);
void		ft_exec2(t_data *data, int argc, char **argv);
int			get_here_doc(char *argv, t_data *data);
void		check_flag(int argc, char **argv, t_data *data);
void		here_doc(t_data *data, int argc, char **argv);

#endif