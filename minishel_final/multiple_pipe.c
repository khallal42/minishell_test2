#include "minishell.h"

int	ft_strcmp_un(char *tmp, char *mv)
{
	int	i;

	i = 0;
	if(!tmp)
		return (0);
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
	if(!s_path)
		return (NULL);
	if(ft_strchr(cmd, '/') && access(cmd, X_OK) == -1)
		return (cmd);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (s_path[i])
	{
		k = ft_strjoin0(s_path[i], "/");
		k = ft_strjoin0(k, cmd);
		if (access(k, X_OK) == 0)
			return (k);
		i++;
	}
	//(perror("cmd  : command not found"),exit(1));
	return (NULL);
}

void	multiple(t_data *m, char **env)
{
	int fdp[2];
	int i;
	int fd = -1;
	int pid;
	int fd1 = -1;
	char **k;
	//char **l;
	char *cmd;
	int track = 0;
	int j = 0;
	//t_list *m;
	// if(m == NULL)
	// 	return ;

	if (pipe(fdp) == -1)
		(perror(""), exit(EXIT_FAILURE));
	i = fork();
	//child
	if (i == 0)
	{
		while (m->infile[j])
		{
			//printf("--------%s\n", m->infile[j]);
			fd = open(m->infile[j], O_RDONLY);
			//printf("$$$$$$$%d\n", fd);
			if (fd == -1)
				(perror(""), exit(EXIT_FAILURE));
			j++;
		}
		if (fd != -1)
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
	//parent
	else
	{
		m = m->next;
		close(fdp[1]);
		track = fdp[0];
		while (m->next)
		{
			if (pipe(fdp) == -1)
				(perror(""), exit(EXIT_FAILURE));
			i = fork();
			if (i == 0)
			{
				close(fdp[0]);
				dup2(track, 0);
				dup2(fdp[1], 1);
				k = split_path(env);
				cmd = ft_access(k, m->full_cmd[0]);
				execve(cmd, m->full_cmd, NULL);
			}
			else
			{
				close(fdp[1]);
				close(track);
				track = fdp[0];
				m = m->next;
			}
		}
		pid = fork();
		if (pid == -1)
			(perror("fork()4"), exit(EXIT_FAILURE));
		if (pid == 0)
		{
			while (m->outfile[j])
			{
				fd1 = open(m->outfile[j], O_RDWR | O_CREAT | O_TRUNC, 0644);
				j++;
				if (fd1 == -1)
					(perror("open()5"), exit(EXIT_FAILURE));
			}
			if (fd1 != -1)
				dup2(fd1, 1); // output nhato f lfille fd1
			dup2(track, 0);   // n9ra dak chi mn l pipe fdp[0]
			k = split_path(env);
			cmd = ft_access(k, m->full_cmd[0]);
			execve(cmd, m->full_cmd, NULL);
		}
	}
	close(track);
	while (waitpid(0, 0, 0) > 0)
		;
	// waitpid(pid, NULL, 0);
}