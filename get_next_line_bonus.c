/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:06:00 by eel-alao          #+#    #+#             */
/*   Updated: 2024/04/01 01:34:05 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*update_saver(char *sv)
{
	int		i;
	char	*temp;
	int		x;

	i = 0;
	while (sv[i] && sv[i] != '\n')
		i++;
	if (sv[i] == '\n')
		i++;
	temp = (char *)malloc((ft_strlen(sv) - i + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	x = 0;
	while (sv[i] != '\0')
		temp[x++] = sv[i++];
	temp[x] = '\0';
	free(sv);
	return (temp);
}

char	*bring_new_line(char *buff)
{
	int		i;
	int		j;
	char	*container;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	container = (char *)malloc((i + 1) * sizeof(char));
	if (!container)
		return (NULL);
	j = 0;
	while (buff[j] && j < i)
	{
		container[j] = buff[j];
		j++;
	}
	container[i] = '\0';
	return (container);
}

int	check_it(char *str, int c)
{
	int	j;

	j = 0;
	if (!str)
		return (0);
	while (str[j])
	{
		if (str[j] == (char)c)
			return (1);
		j++;
	}
	return (0);
}

char	*get_content(int fd, char *content)
{
	char	*str;
	ssize_t	bytes;

	bytes = 1;
	while (bytes > 0 && check_it(content, '\n') == 0)
	{
		str = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
		if (!str)
			return (NULL);
		bytes = read(fd, str, BUFFER_SIZE);
		if (bytes == -1)
		{
			return (free_me(content, str));
		}
		str[bytes] = '\0';
		content = ft_strjoin(content, str);
		if (!content)
			return (NULL);
	}
	return (content);
}

char	*get_next_line(int fd)
{
	static char	*saver[10024];
	char		*line;

	if (BUFFER_SIZE < 0 || fd < 0 || fd > 10024)
		return (NULL);
	saver[fd] = get_content(fd, saver[fd]);
	if (!saver[fd] || saver[fd][0] == '\0')
	{
		free(saver[fd]);
		saver[fd] = NULL;
		return (NULL);
	}
	line = bring_new_line(saver[fd]);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	saver[fd] = update_saver(saver[fd]);
	return (line);
}

int main (void)
{
   int fd1 = open("tests/test.txt", O_RDONLY);
   int fd2 = open("tests/test2.txt", O_RDONLY);
   int fd3 = open("tests/test3.txt", O_RDONLY);
   char *a = get_next_line(fd1);
	char *b = get_next_line(fd2);
	char *c = get_next_line(fd3);
	
	while (a || b || c)
	{
		printf("%s%s%s", a,b,c);
		a = get_next_line(fd1);
		b = get_next_line(fd2);
		c = get_next_line(fd3);
	}
	
   // while (i < 7)
   // {
   //    a = get_next_line(fd1);
   //    printf("line [%02d]: %s", i, a);
	// 	free(a);
	// 	a = get_next_line(fd2);
   //    printf("line [%02d]: %s", i, a);
	// 	free(a);
	// 	a = get_next_line(fd3);
   //    printf("line [%02d]: %s", i, a);
	// 	free(a);
	// 	i++;
   // }
	
}

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
//    int      fd4;

// 	fd1 = open("tests/test.txt", O_RDONLY);
// 	fd2 = open("tests/test2.txt", O_RDONLY);
// 	fd3 = open("tests/test3.txt", O_RDONLY);
// 	fd4 = 74390023;
// 	i = 1;
// 	while (i < 7)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd3);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
      
// 		line = get_next_line(fd4);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		i++;
// 	} 
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);
// 	return (0);
// }