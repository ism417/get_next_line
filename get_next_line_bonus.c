/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:52:50 by eismail           #+#    #+#             */
/*   Updated: 2024/01/17 21:49:26 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*re_line(char **s)
{
	int		i;
	char	*temp;
	char	*line;

	i = find_line(*s);
	if (i == -1)
	{
		line = sub_buf(*s, 0, ft_strlen(*s) - 1);
		free (*s);
		*s = NULL;
		return (line);
	}
	line = sub_buf(*s, 0, i);
	if (!line)
		return (ft_free(NULL, s), NULL);
	temp = sub_buf(*s, i + 1, ft_strlen(*s) - 1);
	free (*s);
	*s = NULL;
	*s = temp;
	return (line);
}

char	*ft_free(char *temp, char **s)
{
	if (*s)
	{
		free (*s);
		*s = NULL;
	}
	free (temp);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char static	*next_line[OPEN_MAX];
	char		*cup_buffer;
	ssize_t		count;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	cup_buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!cup_buffer)
		return (ft_free(NULL, &next_line[fd]), NULL);
	count = 42;
	while ((find_line(next_line[fd]) == -1) && count > 0)
	{
		count = read(fd, cup_buffer, BUFFER_SIZE);
		if (count < 0)
			return (ft_free(cup_buffer, &next_line[fd]));
		cup_buffer[count] = '\0';
		next_line[fd] = add_buffer(next_line[fd], cup_buffer);
		if (!next_line[fd] || !next_line[fd][0])
			return (ft_free(cup_buffer, &next_line[fd]));
	}
	free (cup_buffer);
	return (re_line(&next_line[fd]));
}
