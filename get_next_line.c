/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:51:04 by kcheong           #+#    #+#             */
/*   Updated: 2022/07/13 14:51:04 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*store_extra(char *storage)
{
	int		i;
	int		j;
	char	*extra;

	i = 0;
	j = 0;
	extra = NULL;
	while (storage[i] != '\0' && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
	{
		i++;
		extra = ft_calloc(ft_strlen(storage) - i + 1, sizeof(char));
		while (storage[i] != '\0')
			extra[j++] = storage[i++];
	}
	return (extra);
}

char	*return_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	while (storage[i] != '\0' && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] != '\0' && storage[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *buffer)
{
	int		byteread;
	char	*storage;

	byteread = 1;
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		buffer[byteread] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	free (buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (!storage)
		storage = ft_calloc(1, 1);
	storage = read_file(fd, storage);
	line = return_line(storage);
	storage = store_extra(storage);
	return (line);
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	// get_next_line(fd);
}
