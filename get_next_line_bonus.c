/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:25:18 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/10 14:48:43 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*#include <stdio.h>
#include <fcntl.h>
#define BUFFER_SIZE 1*/

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	if (buf == NULL)
		return (NULL);
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
	next_line = (char *)ft_calloc((ft_strlen(s_bfr) - i) + 1, (sizeof(char)));
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
	s = (char *) ft_calloc((i + 2), sizeof(char));
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
		s = (char *) ft_calloc(1, sizeof(char));
	b = (char *)(ft_calloc(BUFFER_SIZE + 1, sizeof(char)));
	bytes_r = 1;
	while (bytes_r > 0)
	{
		bytes_r = read(fd_, b, BUFFER_SIZE);
		if (bytes_r == -1)
		{
			free(b);
			free(s);
			return (NULL);
		}
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
	static char	*bfr[216];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 216)
		return (NULL);
	bfr[fd] = read_file(fd, bfr[fd]);
	if (!bfr[fd])
		return (NULL);
	line = ft_line(bfr[fd]);
	bfr[fd] = ft_next_line(bfr[fd]);
	return (line);
}
