/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 04:22:46 by plopez-b          #+#    #+#             */
/*   Updated: 2025/06/07 13:12:01 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "designer.h"
#include <fcntl.h>
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int	error(char *reason)
{
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(reason, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}

static void	draw_map(t_game *game)
{
	char	c;
	int		color;

	for (int x = 0; x < game->width; x += 1)
	{
		for (int y = 0; y < game->height; y += 1)
		{
			c = game->map[(x + 1) + (y + 1) * (game->width + 2)];
			color = 0;
			for (int sx = 0; sx < GRID_SIZE; sx += 1)
			{
				for (int sy = 0; sy < GRID_SIZE; sy += 1)
				{
					if (c == '0')
						color = 0xffffffff;
					else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
						color = 0xaa0000ff;
					mlx_put_pixel(game->buffer, x * GRID_SIZE + sx, y
							* GRID_SIZE + sy, color);
				}
			}
		}
	}
}

static void	draw_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	if (game->buffer)
		mlx_delete_image(game->mlx, game->buffer);
	game->buffer = mlx_new_image(game->mlx, game->width * GRID_SIZE,
			game->height * GRID_SIZE);
	if (!game->buffer)
		return ;
	draw_map(game);
	mlx_image_to_window(game->mlx, game->buffer, 0, 0);
}

static void	delete_starting_positions(t_game *game)
{
	for (int x = 0; x < game->width; x += 1)
	{
		for (int y = 0; y < game->height; y += 1)
		{
			if (game->map[(x + 1) + (y + 1) * (game->width + 2)] == 'N'
				|| game->map[(x + 1) + (y + 1) * (game->width + 2)] == 'S'
				|| game->map[(x + 1) + (y + 1) * (game->width + 2)] == 'W'
				|| game->map[(x + 1) + (y + 1) * (game->width + 2)] == 'E')
				game->map[(x + 1) + (y + 1) * (game->width + 2)] = '0';
		}
	}
}

static void	cursor_hook(double x_pos, double y_pos, void *param)
{
	t_game	*game;
	int		horizontal;
	int		vertical;

	game = (t_game *)param;
	horizontal = x_pos / GRID_SIZE + 1;
	vertical = y_pos / GRID_SIZE + 1;
	if (horizontal < 0 || horizontal > game->width || vertical < 0
		|| vertical > game->height)
		return ;
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		game->map[(horizontal) + (vertical) * (game->width + 2)] = '0';
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_RIGHT))
		game->map[(horizontal) + (vertical) * (game->width + 2)] = ' ';
	if (mlx_is_key_down(game->mlx, MLX_KEY_N))
	{
		delete_starting_positions(game);
		game->map[(horizontal) + (vertical) * (game->width + 2)] = 'N';
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		delete_starting_positions(game);
		game->map[(horizontal) + (vertical) * (game->width + 2)] = 'S';
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_E))
	{
		delete_starting_positions(game);
		game->map[(horizontal) + (vertical) * (game->width + 2)] = 'E';
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		delete_starting_positions(game);
		game->map[(horizontal) + (vertical) * (game->width + 2)] = 'W';
	}
}

static void	surround_with_walls(t_game *game)
{
	for (int row = 1; row <= game->width + 1; row += 1)
	{
		for (int column = 1; column <= game->height + 1; column += 1)
		{
			if (game->map[(row) + (column) * (game->width + 2)] == '0'
				|| game->map[(row) + (column) * (game->width + 2)] == 'N'
				|| game->map[(row) + (column) * (game->width + 2)] == 'S'
				|| game->map[(row) + (column) * (game->width + 2)] == 'W'
				|| game->map[(row) + (column) * (game->width + 2)] == 'E')
			{
				if (game->map[(row - 1) + (column - 1) * (game->width
						+ 2)] == ' ')
					game->map[(row - 1) + (column - 1) * (game->width
							+ 2)] = '1';
				if (game->map[(row - 1) + (column) * (game->width + 2)] == ' ')
					game->map[(row - 1) + (column) * (game->width + 2)] = '1';
				if (game->map[(row) + (column - 1) * (game->width + 2)] == ' ')
					game->map[(row) + (column - 1) * (game->width + 2)] = '1';
				if (game->map[(row + 1) + (column - 1) * (game->width
						+ 2)] == ' ')
					game->map[(row + 1) + (column - 1) * (game->width
							+ 2)] = '1';
				if (game->map[(row + 1) + (column + 1) * (game->width
						+ 2)] == ' ')
					game->map[(row + 1) + (column + 1) * (game->width
							+ 2)] = '1';
				if (game->map[(row + 1) + (column) * (game->width + 2)] == ' ')
					game->map[(row + 1) + (column) * (game->width + 2)] = '1';
				if (game->map[(row) + (column + 1) * (game->width + 2)] == ' ')
					game->map[(row) + (column + 1) * (game->width + 2)] = '1';
				if (game->map[(row - 1) + (column + 1) * (game->width
						+ 2)] == ' ')
					game->map[(row - 1) + (column + 1) * (game->width
							+ 2)] = '1';
			}
		}
	}
}

static int	first_column(t_game *game)
{
	int	first_column;

	game->start_column = game->width;
	for (int row = 0; row < game->height; row += 1)
	{
		first_column = 0;
		while (first_column < game->width && game->map[first_column + row
			* (game->width + 2)] == ' ')
			first_column += 1;
		if (first_column < game->start_column)
			game->start_column = first_column;
	}
}

static int	first_row(t_game *game)
{
	game->start_row = game->height + 2;
	for (int row = 0; row < game->height + 2; row += 1)
	{
		for (int col = 0; col < game->width + 2; col += 1)
		{
			if (game->map[col + row * (game->width + 2)] != ' '
				&& game->start_row > row)
				game->start_row = row;
		}
	}
}

static int	last_row(t_game *game)
{
	char	c;

	game->end_row = 0;
	for (int row = game->height + 1; row >= 0; row -= 1)
	{
		for (int col = 0; col < game->width + 2; col += 1)
		{
			c = game->map[col + row * (game->width + 2)];
			if (c != ' ' && c != '\0' && game->end_row < row)
				game->end_row = row;
		}
	}
}

static void	write_row(t_game *game, int row)
{
	int	last_space;

	last_space = game->width + 1;
	while (last_space > 0 && game->map[row * (game->width + 2)
		+ last_space] == ' ')
		last_space -= 1;
	for (int c = game->start_column; c <= last_space; c += 1)
	{
		write(game->fd, game->map + row * (game->width + 2) + c, 1);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		column;

	// Read commandline arguments
	if (argc != 4)
		return (error("invalid arguments"));
	game.width = atoi(argv[1]);
	game.height = atoi(argv[2]);
	game.name = argv[3];
	// Create filename
	game.filename = ft_strjoin(game.name, ".cub");
	if (!game.filename)
		return (error("unable to create filename string"));
	// Open file for writing
	game.fd = open(game.filename, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (game.fd == -1)
		return (error(game.filename));
	// Alloc space for map and initialize with spaces
	game.map = malloc((game.width + 2) * (game.height + 2));
	if (!game.map)
		return (error("unable to alloc memory for map"));
	for (int pos = 0; pos < (game.width + 2) * (game.height + 2); pos += 1)
		game.map[pos] = ' ';
	// Initialize window and buffer
	game.mlx = mlx_init(game.width * GRID_SIZE, game.height * GRID_SIZE,
			game.filename, false);
	if (!game.mlx)
		return (error("unable to init mlx"));
	game.buffer = (mlx_image_t *)0;
	// Set hooks and start loop
	mlx_loop_hook(game.mlx, draw_hook, (void *)&game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	mlx_loop(game.mlx);
	// Clean mlx
	if (game.buffer)
		mlx_delete_image(game.mlx, game.buffer);
	mlx_terminate(game.mlx);
	// Write empty scene headers
	write(game.fd, "NO ./assets/wolf1.png\n", 22);
	write(game.fd, "SO ./assets/wolf1.png\n", 22);
	write(game.fd, "WE ./assets/wolf1.png\n", 22);
	write(game.fd, "EA ./assets/wolf1.png\n\n", 23);
	write(game.fd, "C 255,255,255\n", 14);
	write(game.fd, "F 255,255,255\n\n", 15);
	surround_with_walls(&game);
	// Save map
	first_column(&game);
	first_row(&game);
	last_row(&game);
	for (int row = game.start_row; row <= game.end_row; row += 1)
	{
		write_row(&game, row);
		write(game.fd, "\n", 1);
	}
	// Clean game
	free(game.map);
	free(game.filename);
	close(game.fd);
	// Exit success
	return (0);
}
