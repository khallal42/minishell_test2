#include "minishell.h"

int	ft_strcmp_un(char *tmp, char *mv)
{
	int	i;

	i = 0;
	while (tmp[i] && mv[i] && tmp[i] != '=')
	{
		if (tmp[i] != mv[i])
			return (0);
		i++;
	}
	return (1);
}

char	**split_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strcmp_un(env[i], "PATH"))
		i++;
	if (ft_strcmp_un(env[i], "PATH"))
		return (ft_split(&env[i][5], ':'));
	else if (!env[i])
	{
		write(1, "path not exist", 15);
		return (NULL);
	}
	else
		return (NULL);
}

char	*ft_access(char **s_path, char *cmd)
{
	char	*k;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	// printf("%s\n", cmd);
	// while (s_path[i])
	// {
	// 	printf("------%s\n", s_path[i]);
	// 	i++;
	// }
	// i = 0;
	while (s_path[i])
	{
		k = ft_strjoin0(s_path[i], "/");
		k = ft_strjoin0(k, cmd);
		if (access(k, X_OK) == 0)
			return (k);
		i++;
	}
	return (NULL);
}

void	multiple(t_data *m, char **env)
{
	int fdp[2];
	int i;
	int fd;
	int pid;
	int fd1;
	char **k;
	//char **l;
	char *cmd;
	int track;
	int j = 0;
	//t_list *m;
	if(m == NULL)
		return ;

	if (pipe(fdp) == -1)
		(perror("pipe()"), exit(EXIT_FAILURE));
	i = fork();
	if (i == 0)
	{
		while (m->infile[j])
		{
			fd = open((*m->infile), O_RDONLY);
			if (fd == -1)
				(perror("open()"), exit(EXIT_FAILURE));
			j++;
		}
		if(fd != -1)
			dup2(fd, 0); //ghadi ywali lfille.txt howa input
		close(fdp[0]);
		dup2(fdp[1], 1); // ghadi nhat l output dyal l command f pipe
		k = split_path(env);
		//l = ft_split(m->full_cmd, ' ');
		//printf("--------------(%s)\n", m->full_cmd[0]);
		cmd = ft_access(k, m->full_cmd[0]);
		//s1[] = {l, NULL};
		execve(cmd, m->full_cmd, NULL);
	}
	m = m->next;
	while (m->next)
	{
		i = fork();
		if (i == 0)
		{
			track = fdp[0];
			close(fdp[0]);
			if (pipe(fdp) == -1)
				(perror("pipe()"), exit(EXIT_FAILURE));
			dup2(fdp[0], track);
			close(fdp[1]);
			k = split_path(env);
			cmd = ft_access(k, m->full_cmd[0]);
			execve(cmd, m->full_cmd, NULL);
		}
		m = m->next;
	}
	pid = fork();
	if (pid == -1)
		(perror("fork()"), exit(EXIT_FAILURE));
	if (pid == 0)
	{
		//printf("jjjjjj\n");
		fd1 = open(m->outfile[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(fd1, 1); // output nhato f lfille fd1
		close(fdp[1]);
		dup2(fdp[0], 0); // n9ra dak chi mn l pipe fdp[0]
		k = split_path(env);
		//l = ft_split(av[2], ' ');
		cmd = ft_access(k, m->full_cmd[0]);
		execve(cmd, m->full_cmd, NULL);
	}
	while (waitpid(0, 0, 0) < 0)
		;
	// waitpid(pid, NULL, 0);
}