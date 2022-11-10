#include "../includes/cub3d.h"

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		((unsigned char *)b)[i] = (unsigned char)c;
// 		i++;
// 	}
// 	return (b);
// }

// void	ft_bzero(void *s, size_t n)
// {
// 	ft_memset(s, '\0', n);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*mem;

// 	if (count == 0 || size == 0)
// 	{
// 		count = 1;
// 		size = 1;
// 	}
// 	if (count > SSIZE_MAX / size)
// 		return (NULL);
// 	mem = malloc(count * size);
// 	if (mem)
// 		ft_bzero(mem, count * size);
// 	return (mem);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

void	error_and_exit()
{
	printf("Map invalid!");
	exit(1);
}

void	free_map_str(char **map_str, long long map_height)
{
	long long i;

	i = 0;
	while (i < map_height)
		free(map_str[i++]);
	free(map_str);
}

void	free_is_checked(bool **is_checked, long long map_height)
{
	long long i;

	i = 0;
	while (i < map_height)
		free(is_checked[i++]);
	free(is_checked);
}


bool flood_fill_2(char **map_str, bool **is_checked, long long x, long long y, long long map_width, long long map_height)
{
	if (x >= map_width || y >= map_height || x < 0 || y < 0)
		return (false);
	if (is_checked[x][y] == true)
		return (true);
	if (map_str[x][y] == '1')
		return (true);
	else
		is_checked[x][y] = true;
	if (flood_fill_2(map_str, is_checked, x, y - 1, map_width, map_height) == false)
		return (false);
	if (flood_fill_2(map_str, is_checked, x - 1, y, map_width, map_height) == false)
		return (false);
	if (flood_fill_2(map_str, is_checked, x, y + 1, map_width, map_height) == false)
		return (false);
	if (flood_fill_2(map_str, is_checked, x + 1, y, map_width, map_height) == false)
		return (false);
	return (true);
}

long long get_map_height(char **map_str)
{
	long long i;

	i = 0;
	while (map_str[i])
		i++;
	if (i <= 2)
		error_and_exit();
	return i;
}

long long get_map_width_max(char **map_str)
{
	long long i;
	long long max_width;
	long long width;

	i = 0;
	max_width = 0;
	while (map_str[i])
	{
		width = ft_strlen(map_str[i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	if (max_width <= 2)
		error_and_exit();
	return (max_width);
}

// void flood_fill(char **map_str, long long map_width, long long map_height)
void	flood_fill(char **map_str, long long pos_x, long long pos_y)
{
	bool **is_checked;
	long long map_width;
	long long map_height;
	long long i;

	map_width = get_map_width_max(map_str);
	map_height = get_map_height(map_str);
	is_checked = (bool **)malloc(sizeof(bool *) * map_height);
	if (!is_checked)
		exit(1);
	i = 0;
	while (i < map_height)
	{
		is_checked[i] = (bool *)ft_calloc(sizeof(bool), map_width + 1);
		if (!is_checked[i])
			exit(1);
		i++;
	}
	if (flood_fill_2(map_str, is_checked, pos_x, pos_y, map_width, map_height) == false)
		error_and_exit();
	else
		printf("Map OK!");
	free_is_checked(is_checked, map_height);
	free_map_str(map_str, map_height);
}

// void main()
// {
// 	long long map_width;
// 	long long map_height;
// 	long long i;

// 	char **map_str = (char **)malloc(sizeof(char *) * 6);
// 	if (!map_str)
// 		exit(1);
// 	i = 0;
// 	// while (i < 5)
// 	// {
// 	// 	map_str[i] = (char *)malloc(7);
// 	// 	if (!map_str[i])
// 	// 		exit(1);
// 	// 	i++;
// 	// }
// 	map_str[0] = "1 11 1";
// 	map_str[1] = "110010";
// 	map_str[2] = "10N010";
// 	map_str[3] = "100010";
// 	map_str[4] = "111110";
// 	map_str[5] = NULL;

// 	map_width = get_map_width_max(map_str);
// 	if (map_width <= 2)
// 		error_and_exit();
// 	map_height = get_map_height(map_str);
// 	if (map_height <= 2)
// 		error_and_exit();
// 	flood_fill(map_str, map_width, map_height);

// 	i = 0;
// 	// while (i < 5)
// 	// 	free(map_str[i++]);
// 	free(map_str);
// }
