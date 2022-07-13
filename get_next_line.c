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

char	*return_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_calloc(1, 1);
	while (storage[i] != '\0' && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] != '\0' && storage[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	char	*storage;
	char	*buffer;
	int		byteread;

	storage = 0;
	if (!storage)
		storage = ft_calloc(1, 1);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	byteread = 1;
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		buffer[byteread] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (ft_strchr(storage, '\n'))
			storage = return_line(storage);
	}
	return (storage);
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	// get_next_line(fd);
}