/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:41:21 by hrakik            #+#    #+#             */
/*   Updated: 2023/02/20 14:36:21 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_prompt
{
	char			*cmds;
	char			*all;
	char			*st;
	int				quots;
	int				single_quots;
	int				dola;
	struct s_prompt	*next;
}					t_prompt;

typedef struct s_data
{
	char			**full_cmd;
	char			**infile;
	char			**outfile;
	struct s_data	*next;
}					t_data;

// int		ft_check_empt(char *s);
// void	lexer(t_prompt *prompt);
char				**ft_split(char *s, char c);
void				expand_Path(char **a, char **env);
void				msg_err(char *err);
void				msg_error(char *err);
void				msg_cmd_not_found(char *s);

//=======
char				**ft_cmdtrim(char const *s, char *set);
char				**break_cmd(char *s, char set);
int					count_word(char *s, char set);
// static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3]);
// static int	ft_count_words(const char *s, char *c, int i[2]);
void				ft_cmdsubsplit(char *s, char *set);
//========
void				divide_input(char **av, t_data **data);
//============
void				create_node(t_data **data, char **infile, char **outfile,
						char **full_cmd);
t_data				*l_lstlast(t_data **lst);
t_data				*l_lstnew(char **infile, char **outfile, char **full_cmd);
void				l_lstadd_back(t_data **lst, t_data *new);
int					l_lstsize(t_data *lst);
int					skip_infile(char **s);
void				multiple(t_data *m, char **env);
size_t				ft_strlen0(char *s);
char	*ft_strjoin0(char *s1, char *s2);
//char				**ft_split(char const *s, char c);

#endif