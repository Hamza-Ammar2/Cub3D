#include "cub3d.h"

static int	parse_rgb_component(char *part, int *rgb_value)
{
	if (!is_valid_number(part))
		return (-1);
	*rgb_value = ft_atoi(part);
	if (*rgb_value < 0 || *rgb_value > 255)
		return (-1);
	return (0);
}

static int	parse_rgb_parts(char **parts, int *rgb_values)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (parse_rgb_component(parts[i], &rgb_values[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	split_rgb_parts(char *str, char ***parts)
{
	*parts = ft_split(str, ',');
	if (!*parts || count_words(*parts) != 3)
	{
		free_split(*parts);
		return (-1);
	}
	return (0);
}

int	parse_rgb(char *str)
{
	char	**parts;
	int		rgb_values[3];

	if (split_rgb_parts(str, &parts) != 0)
		return (-1);
	if (parse_rgb_parts(parts, rgb_values) != 0)
	{
		free_split(parts);
		return (-1);
	}
	free_split(parts);
	return ((rgb_values[0] << 16) | (rgb_values[1] << 8) | rgb_values[2]);
}
