/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:18:57 by bvernimm          #+#    #+#             */
/*   Updated: 2022/01/20 11:24:39 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_linelen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*ft_new_file(char *file)
{
	int		line_len;
	int		i;
	char	*new;

	i = 0;
	line_len = ft_linelen(file);
	if (!file[line_len])
	{
		free(file);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_strlen(file) - line_len + 1));
	if (!new)
		return (NULL);
	line_len++;
	while (file[line_len])
	{
		new[i] = file[line_len];
		i++;
		line_len++;
	}
	new[i] = '\0';
	free (file);
	return (new);
}

char	*ft_read_file(int fd, char *file)
{
	int		nbr_char;
	char	*tmp;

	tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	nbr_char = 1;
	while (!ft_strchr(file, '\n') && nbr_char != 0)
	{
		nbr_char = read(fd, tmp, BUFFER_SIZE);
		if (nbr_char < 0)
		{
			free (tmp);
			return (NULL);
		}
		tmp[nbr_char] = '\0';
		file = ft_strjoin(file, tmp);
		if (!file)
			return (NULL);
	}
	free(tmp);
	return (file);
}

char	*ft_get_line(char *file)
{
	int		line_len;
	int		i;
	char	*tmp;

	i = 0;
	if (!file[i])
		return (NULL);
	line_len = ft_linelen(file);
	tmp = malloc(sizeof(char) * line_len + 2);
	if (!tmp)
		return (NULL);
	while (i <= line_len)
	{
		tmp[i] = file[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*file[1000];
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file[fd] = ft_read_file(fd, file[fd]);
	if (!file[fd])
		return (NULL);
	res = ft_get_line(file[fd]);
	file[fd] = ft_new_file(file[fd]);
	return (res);
}
