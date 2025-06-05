/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:38:28 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/20 19:30:58 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "caster.h"
#include <MLX42/MLX42.h>

static void	draw_horizontal_line(t_game *game, int y)
{
	int	pixel_x;

	pixel_x = 0;
	while (pixel_x < WIDTH)
	{
		mlx_put_pixel(game->buffer, pixel_x, y, 0x505050FF);
		pixel_x += 1;
	}
}

static void	draw_vertical_line(t_game *game, int x)
{
	int	pixel_y;

	pixel_y = 0;
	while (pixel_y < HEIGHT)
	{
		mlx_put_pixel(game->buffer, x, pixel_y, 0x505050FF);
		pixel_y += 1;
	}
}

void	draw_grid(t_game *game)
{
	int	vertical_line;
	int	horizontal_line;

	vertical_line = 0;
	while (vertical_line < WIDTH)
	{
		draw_vertical_line(game, vertical_line);
		vertical_line += GRID_SIZE;
	}
	horizontal_line = 0;
	while (horizontal_line < HEIGHT)
	{
		draw_horizontal_line(game, horizontal_line);
		horizontal_line += GRID_SIZE;
	}
}

void	draw_point(t_game *game, t_point *point, int color)
{
	int	point_x;
	int	point_y;

	point_x = (int)(point->x * GRID_SIZE);
	point_y = (int)(point->y * GRID_SIZE);
	if (point_x < 1 || point_x > WIDTH - 2
		|| point_y < 1 || point_y > HEIGHT - 2)
		return ;
	mlx_put_pixel(game->buffer, point_x - 1, point_y - 1, color);
	mlx_put_pixel(game->buffer, point_x - 1, point_y, color);
	mlx_put_pixel(game->buffer, point_x - 1, point_y + 1, color);
	mlx_put_pixel(game->buffer, point_x, point_y - 1, color);
	mlx_put_pixel(game->buffer, point_x, point_y, color);
	mlx_put_pixel(game->buffer, point_x, point_y + 1, color);
	mlx_put_pixel(game->buffer, point_x + 1, point_y - 1, color);
	mlx_put_pixel(game->buffer, point_x + 1, point_y, color);
	mlx_put_pixel(game->buffer, point_x + 1, point_y + 1, color);
}
