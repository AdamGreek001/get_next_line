/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:20:26 by eel-alao          #+#    #+#             */
/*   Updated: 2024/04/01 01:08:26 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*saver;
	char		*line;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	saver = get_content(fd, saver);
	if (!saver || saver[0] == '\0')
	{
		free(saver);
		saver = NULL;
		return (NULL);
	}
	line = bring_new_line(saver);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	saver = update_saver(saver);
	return (line);
}

int main (void)
{
   int fd1 = open("tests/test.txt", O_RDONLY, 0777);
   char *a;

   while (a)
   {
      a = get_next_line(fd1);
      printf("%s", a);
   } 
}
