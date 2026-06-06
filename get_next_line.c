/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapena-z <mapena-z@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:41:23 by mapena-z          #+#    #+#             */
/*   Updated: 2026/06/04 10:30:12 by mapena-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *str)
{
	char	*new_str_line;
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(str, ' '))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		new_str_line = ft_strjoin(str, buffer);
		free(str);
		str = new_str_line;
	}
	free(buffer);
	return (str);
}

static char	*get_line(char *str)
{
	int		len;
	char	*new_str;

	if (!str || !str[0])
		return (NULL);
	len = 0;
	while (str[len] != ' ' && str[len])
		len++;
	if (str[len] == ' ')
		new_str = ft_substr(str, 0, len + 1);
	else
		new_str = ft_substr(str, 0, len);
	return (new_str);
}

static char	*get_rest(char *str)
{
	int		len;
	char	*rest;

	len = 0;
	while (str[len] != ' ' && str[len])
		len++;
	if (!str[len])
	{
		free(str);
		return (NULL);
	}
	rest = ft_substr(str, len + 1, ft_strlen(str) - len - 1);
	free(str);
	return (rest);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!str)
		str = ft_strdup("");
	if (!str)
		return (NULL);
	str = read_line(fd, str);
	if (!str)
		return (str = NULL, NULL);
	if (!str[0])
	{
		free(str);
		return (str = NULL, NULL);
	}
	line = get_line(str);
	str = get_rest(str);
	return (line);
}

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int	fd;
	char *str1;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		str1 = get_next_line(fd);
		if (str1 == NULL)
			break ;
		printf("%s", str1);
		printf("\n");
		free(str1);
	}
	close(fd);
	return (0);
}