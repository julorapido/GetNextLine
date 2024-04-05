/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julessainthorant <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:14:25 by julessainthor     #+#    #+#             */
/*   Updated: 2024/04/05 23:33:17 by julessainthor    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

//#include <stdio.h>
//#include <fcntl.h>
//#define BUFFER_SIZE 1

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_next_line(char *s_bfr)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	while (s_bfr[i] && s_bfr[i] != '\n')
		i++;
	if (!s_bfr[i])
	{
		free(s_bfr);
		return (NULL);
	}
	next_line = (char *)malloc((ft_strlen(s_bfr) - i) + 1 * (sizeof(char)));
	i++;
	j = 0;
	while (s_bfr[i])
		next_line[j++] = s_bfr[i++];
	free(s_bfr);
	return (next_line);
}

char	*ft_line(char *buffer)
{
	char	*s;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	s = (char *) malloc((i + 2) * sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		s[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		s[i++] = '\n';
	return (s);
}

char	*read_file(int fd_, char *s)
{
	char	*b;
	int		bytes_r;

	if (!s)
		s = (char *) malloc(1 * sizeof(char));
	b = (char *)(malloc(BUFFER_SIZE + 1 * sizeof(char)));
	bytes_r = 1;
	while (bytes_r > 0)
	{
		bytes_r = read(fd_, b, BUFFER_SIZE);
		b[bytes_r] = '\0';
		s = ft_free(s, b);
		if (ft_strchr(b, '\n'))
			break ;
	}
	free(b);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*bfr;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	bfr = read_file(fd, bfr);
	if (!bfr)
		return (NULL);
	line = ft_line(bfr);
	bfr = ft_next_line(bfr);
	return (line);
}
/*
int main(int argc, char **argv)
{
	char* fileName = "file.txt";
    int fd = open(fileName, O_RDWR);

    if(fd == -1){
		printf("\nError Opening File!!\n");
		exit(1);
    }
    else{
		printf("\nFile %s opened sucessfully!\n", fileName);
    }
	printf("%s \n", get_next_line(fd));
	printf("%s \n", get_next_line(fd));
	printf("%s \n", get_next_line(fd));
	printf("%s \n", get_next_line(fd));
	printf("%s \n", get_next_line(fd));
	printf("%s \n", get_next_line(fd));
	return 0;
}*/