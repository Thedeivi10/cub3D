/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:21:35 by davigome          #+#    #+#             */
/*   Updated: 2025/05/31 22:32:09 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_free_map(t_map *game);

int	ft_count_lines(char *map, t_map *game)
{
	char	*line;
	int		len;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Error\nCould not open the file to count lines.\n");
		ft_free_map(game);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	len = 0;
	while (line)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->height = len;
	return (len);
}

void	ft_free_map(t_map *game)
{
	int	i;

	i = -1;
	if (!game)
		return ;
	if (game->grid)
	{
		while (++i < game->height && game->grid[i])
			free(game->grid[i]);
		free(game->grid);
	}
	free(game);
}

void	ft_read_2(int fd, char *line, t_map *game)
{
	int	i;

	i = 0;
	while (line)
	{
		if (line[0] == '\n')
			game->grid[i] = ft_strdup("\n");
		else if (line[ft_strlen(line) - 1] == '\n' )
			game->grid[i] = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			game->grid[i] = ft_strdup(line);
		if (!game->grid[i])
		{
			fprintf(stderr, "Error\nCould not duplicate line.\n");
			free(line);
			ft_free_map(game);
			exit(EXIT_FAILURE);
		}
		free(line);
		i++;
		line = get_next_line(fd);
	}
	game->grid[i] = NULL;
}

void	ft_read_map(t_map *game, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Error\nCould not open the file properly.\n");
		exit(EXIT_FAILURE);
	}
	game->grid = malloc(sizeof(char *) * (ft_count_lines(argv[1], game) + 1));
	if (!game->grid)
	{
		fprintf(stderr, "Error\nCould not allocate memory for the gird.\n");
		ft_free_map(game);
		 exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		fprintf(stderr, "Error\nThe map is empty\n");
		ft_free_map(game);
		exit(EXIT_FAILURE);
	}
	ft_read_2(fd, line, game);
	close(fd);
}

void	ft_check_name(char **argv)
{
	int len;

	len = ft_strlen(argv[1]);
	if (argv[1][len - 1] != 'b' ||  argv[1][len - 2] != 'u'
		|| argv[1][len - 3] != 'c' || argv[1][len - 4] != '.')
	{
		fprintf(stderr, "Error\nThe map must end with .cub.\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_init_map(t_map *game)
{
	if (!game)
	{
		fprintf(stderr, "Error\nCould not allocate the map");
		exit(EXIT_FAILURE);
	}
	game->grid = NULL;
	game->height = 0;
}

void	ft_init_elem(t_elem *elem)
{
	elem->c = 0;
	elem->f = 0;
	elem->e = 0;
	elem->n = 0;
	elem->s = 0;
	elem->w = 0;
	elem->flag = 0;	
}

void	ft_check_elements_2(t_map *game, t_elem *elem)
{
	if (elem->c > 1 || elem->e > 1 || elem->f > 1
		|| elem->n > 1 || elem->s > 1 || elem->w > 1)
	{
		fprintf(stderr, "Error\nYou must specify each texture one time.\n");
		ft_free_map(game);
		exit(EXIT_FAILURE);
	}
	if (elem->c < 1 || elem->e < 1 || elem->f < 1
		|| elem->n < 1 || elem->s < 1 || elem->w < 1)
	{
		fprintf(stderr, "Error\nYou must specify each texture one time.\n");
		ft_free_map(game);
		exit(EXIT_FAILURE);
	}
	
}

void	ft_check_elements(t_map *game)
{
	t_elem	*elem;
	int		i;

	i = -1;
	while (game->grid[++i])
	{
		if (game->grid[i][0] != 'N' && game->grid[i][0] != 'S'
			&& game->grid[i][0] != 'W' && game->grid[i][0] != 'E'
			&& game->grid[i][0] != 'F' && game->grid[i][0] != 'C'
			&& game->grid[i][0] != '\n')
			break;
		if (game->grid[i][0] != 'N')
			++elem->n;
		if (game->grid[i][0] != 'S')
			++elem->s;
		if (game->grid[i][0] != 'W')
			++elem->w;
		if (game->grid[i][0] != 'E')
			++elem->e;
		if (game->grid[i][0] != 'F')
			++elem->f;
		if (game->grid[i][0] != 'C')
			++elem->c;
	}
	ft_check_elements_2(game, elem);
}

void	ft_checks(t_map *game, char **argv)
{
	ft_check_name(argv);
	ft_init_map(game);
	ft_read_map(game, argv);
	ft_check_elements(game);
}

int main(int argc, char **argv)
{
	t_map *game;
	
	game = malloc(sizeof(t_map));
	if (argc != 2)
		fprintf(stderr, "Error\ncub3D needs a .cub map.\n");
	ft_checks(game, argv);
	return (EXIT_SUCCESS);
}