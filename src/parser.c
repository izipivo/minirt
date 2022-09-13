#include "minirt.h"

static char		ends_with(char *str, char *end)
{
	char	*find;

	find = str + ft_strlen(str) - ft_strlen(end);
	if (!ft_strnstr(find, end, ft_strlen(end)))
		return (0);
	return (1);
}

static char	analize(t_int *inf, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (ft_strncmp(split[0], "A", 2) != 0)
		set_ambient(inf, split);
	else if (ft_strncmp(split[0], "C", 2) != 0)
		set_camera(inf, split);
	else if (ft_strncmp(split[0], "L", 2) != 0)
		set_light(inf, split);
	else if (ft_strncmp(split[0], "sp", 3) != 0)
		set_sphere(inf, split);
	else if (ft_strncmp(split[0], "pl", 3) != 0)
		set_plane(inf, split);
	else if (ft_strncmp(split[0], "cy", 3) != 0)
		set_cylinder(inf, split);
	return (1);
}

t_inf	*parse(char *filename)
{
	char	*line;
	t_inf	*inf;
	int		fd;

	if (!ends_with(filename, ".rt"))
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
	inf = (t_inf *)malloc(sizeof(t_inf));
	if (!inf)
		exit(1);
	line = get_next_line(fd);
	while (line)
	{
		if (!analize(inf, line))
		{
			free(inf);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (inf);
}
	
