/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:51:04 by kcheong           #+#    #+#             */
/*   Updated: 2022/07/23 19:21:53 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// stores extra characters (after \n) so we can keep
// and join them with the text being read next time.
char	*store_extra(char *storage)
{
	int		i;
	int		j;
	char	*extra;

	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
		i++;
	extra = malloc((ft_strlen(storage) - i + 1) * sizeof(char));
	i++;
	j = 0;
	while (storage[i] != '\0')
		extra[j++] = storage[i++];
	free(storage);
	return (extra);
}

// only returns one line from storage.
char	*return_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] != '\0' && storage[i] == '\n')
		line[i++] = '\n';
	return (line);
}

// reads the text file and join the text until it finds \n.
char	*read_join(int fd, char *storage)
{
	int		byteread;
	char	*buffer;

	byteread = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byteread] = 0;
		if (!storage)
			storage = ft_strdup(buffer);
		else
		{
			storage = ft_strjoin(storage, buffer);
			if (ft_strchr(storage, '\n'))
				break ;
		}
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || fd > 1024)
		return (NULL);
	storage = read_join(fd, storage);
	if (!storage || *storage == '\0')
	{
		free(storage);
		return (NULL);
	}
	line = return_line(storage);
	storage = store_extra(storage);
	return (line);
}

int	main(void)
{
	char *res;
	
	int	fd = open("test.txt", O_RDONLY);
	res = get_next_line(fd);
	printf("Result 1 = [%s]\n", res);
	free(res);
	res = get_next_line(fd);
	printf("Result 2 = [%s]\n", res);
	free(res);
	res = get_next_line(fd);
	printf("Result 3 = [%s]\n", res);
	free(res);
	res = get_next_line(fd);
	printf("Result 4 = [%s]\n", res);
	free(res);
	// printf("%s", get_next_line(fd));
	// get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);
}
