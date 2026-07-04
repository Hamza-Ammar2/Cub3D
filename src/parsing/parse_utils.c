#include "cub3d.h"

/* Return 1 if the line contains only whitespace (a blank line), else 0. */
int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Remove a single trailing newline from a line in place; returns the line. */
char	*strip_newline(char *line)
{
	int	length;

	length = ft_strlen(line);
	if (length > 0 && line[length - 1] == '\n')
		line[length - 1] = '\0';
	return (line);
}

/* Count the strings in a NULL-terminated array (e.g. ft_split output). */
int	count_words(char **split)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	return (i);
}

/* Return 1 if the string contains only digits, else 0. */
int	is_valid_number(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
