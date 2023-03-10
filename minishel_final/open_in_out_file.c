/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_in_out_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:47:51 by khallal           #+#    #+#             */
/*   Updated: 2023/03/09 16:48:14 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_outfile(t_minishell *mini, t_data *data)
{
	if (data->outfile != NULL)
	{
		mini->j = 0;
		while (data->outfile[mini->j] != NULL && data->out_open != 0)
		{
			if (data->outfile[mini->j][0] == '>'
				&& data->outfile[mini->j][1] == '>')
			{
				mini->fd1 = open(ft_strtrim_1(data->outfile[mini->j],
												">>"),
									O_RDWR | O_CREAT | O_APPEND,
									0644);
			}
			else
				mini->fd1 = open(data->outfile[mini->j],
									O_RDWR | O_CREAT | O_TRUNC,
									0644);
			if (mini->fd1 < 0)
				(perror("44"), exit(1));
			mini->j++;
			data->out_open--;
		}
	}
	mini->j = 0;
}

void	open_infile(t_minishell *mini, t_data *data, t_here_doc **x, char **env)
{
	int j;

	while (data->infile[mini->j])
	{
		while (check_heredoc(data->infile, mini->j) && data->infile[mini->j]
			&& mini->her != 0)
		{
			if (data->infile[mini->j][0] == '<'
				&& data->infile[mini->j][1] == '<')
			{
				j = here_doc(data->infile[mini->j], mini->j, data, mini, env);
				ft_lstadd_back3(x, ft_lstnew0(j));
			}
			else
			{
				mini->fd = open(data->infile[mini->j], O_RDONLY);
				if (mini->fd == -1)
					mini->fail_open = 1;
				mini->fd = -1;
			}
			mini->j++;
		}
		mini->her = 0;
		if (mini->fail_open == 1)
			(write(2, "  : no such file or directory\n", 31),
				exit(1));
		if (data->infile[mini->j])
		{
			mini->fd = open(data->infile[mini->j], O_RDONLY);
			if (mini->fd == -1)
				(perror("data->infile[mini->j]"), exit(1));
			mini->j++;
		}
	}
}