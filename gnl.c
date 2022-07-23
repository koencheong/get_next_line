#include "get_next_line.h"

char	*store_extra(char *storage)
{
	int		i;
	int		j;
	char	*extra;

	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
		i++;
	extra = ft_calloc((ft_strlen(storage) - i + 1), sizeof(char));
	i++;
	j = 0;
	// printf("Storage that is being brought into store_extra = %s\n", storage);
	while (storage[i] != '\0')
		extra[j++] = storage[i++];
	free(storage);
	// printf("Extra = %s\n", extra);
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

char	*read_file(int fd, char *storage)
{
	int		byteread;
	char	*buffer;

	byteread = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		// printf("[%s]\n", buffer);
		buffer[byteread] = 0;
		if (!storage)
		{
			storage = ft_strdup(buffer);
			// printf("Initial storage = [%s]\n", storage);
		}
		else
		{
			storage = ft_strjoin(storage, buffer);
			// printf("Read until new line is found = [%s]\n", storage);
			if (ft_strchr(storage, '\n'))
				break ;
		}
	}
	free (buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	storage = read_file(fd, storage);
	// printf("Storage while reading the file = %s\n", storage);
	line = return_line(storage);
	storage = store_extra(storage);
	// printf("Line being returned = %s\n", line);
	// printf("Storage after storing extra characters = %s\n", storage);
	return (line);
}

char	*ft_strdup(const char *s1)
{
	char	*temp;
	size_t	i;
	size_t	s1len;

	i = 0;
	s1len = ft_strlen(s1);
	temp = malloc(sizeof(char) * (s1len + 1));
	if (!temp)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
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
