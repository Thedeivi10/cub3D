/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:35:43 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/23 02:54:37 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_.h"

static void	minimap_scale(t_game *game, int *grid_size, int *offset)
{
	*grid_size = SCREEN_HEIGHT * MINIMAP_SCALE / game->height;
	*offset = SCREEN_HEIGHT * (1 - MINIMAP_SCALE);
	if (*grid_size * game->width > SCREEN_WIDTH * MINIMAP_SCALE)
	{
		*grid_size = SCREEN_WIDTH * MINIMAP_SCALE / game->width;
		*offset = SCREEN_HEIGHT - *grid_size * game->height;
	}
}

static void	fill_square(t_game *game, int x, int y)
{
	int	pixel_x;
	int	pixel_y;
	int	grid_size;
	int	offset;

	minimap_scale(game, &grid_size, &offset);
	pixel_x = (grid_size > 1);
	while (pixel_x < grid_size)
	{
		pixel_y = (grid_size > 1);
		while (pixel_y < grid_size)
		{
			mlx_put_pixel(game->buffer, pixel_x + x * grid_size, offset
				+ pixel_y + y * grid_size, 0xAAAAAAFF);
			pixel_y += 1;
		}
		pixel_x += 1;
	}
}

void	draw_point(t_game *game, t_point *point, int color)
{
	int	point_x;
	int	point_y;
	int	grid_size;
	int	offset;

	minimap_scale(game, &grid_size, &offset);
	point_x = (int)(point->x * grid_size);
	point_y = (int)(point->y * grid_size);
	if (point_x < 1 || point_x > game->width * grid_size - 2 || point_y < 1
		|| point_y > game->height * grid_size - 2)
		return ;
	mlx_put_pixel(game->buffer, point_x - 1, offset + point_y - 1, color);
	mlx_put_pixel(game->buffer, point_x - 1, offset + point_y, color);
	mlx_put_pixel(game->buffer, point_x - 1, offset + point_y + 1, color);
	mlx_put_pixel(game->buffer, point_x, offset + point_y - 1, color);
	mlx_put_pixel(game->buffer, point_x, offset + point_y, color);
	mlx_put_pixel(game->buffer, point_x, offset + point_y + 1, color);
	mlx_put_pixel(game->buffer, point_x + 1, offset + point_y - 1, color);
	mlx_put_pixel(game->buffer, point_x + 1, offset + point_y, color);
	mlx_put_pixel(game->buffer, point_x + 1, offset + point_y + 1, color);
}

static void	draw_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->width)
	{
		y = 0;
		while (y < game->height)
		{
			if (game->s_map[y][x] == '0')
				fill_square(game, x, y);
			y += 1;
		}
		x += 1;
	}
}

void	draw_minimap(t_game *game)
{
	t_point	end;

	end.x = game->player.position.x + game->player.direction.x;
	end.y = game->player.position.y + game->player.direction.y;
	draw_map(game);
	draw_point(game, &end, 0xFFAA00FF);
	draw_point(game, &game->player.position, 0x00FFFFFF);
}
