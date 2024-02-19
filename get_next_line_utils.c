/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:43:33 by eel-alao          #+#    #+#             */
/*   Updated: 2024/02/19 21:22:03 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_me(char *v1, char *v2)
{
	if (v1 != NULL)
	{
		free(v1);
		v1 = NULL;
	}
	if (v2 != NULL)
	{
		free(v2);
		v2 = NULL;
	}
	return (NULL);
}

int ft_strlen(char  *str)
{
   size_t   i;
	
	if (!str)
		return(0);
   
   i = 0;
   while (str[i] != '\0')
      i++;
   return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;
	if(!s1)
		return(s2);
	res = malloc (ft_strlen(s1)+ ft_strlen(s2) + 1);
	if (!res)
		return(NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	free(s1);
	s1=NULL;
	free(s2);
	s2=NULL;
	return(res);
}
