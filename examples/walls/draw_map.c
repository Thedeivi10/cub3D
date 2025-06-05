/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:35:43 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/21 17:53:18 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "caster.h"

static void	fill_square(t_game *game, int x, int y)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = 0;
	while (pixel_x < GRID_SIZE)
	{
		pixel_y = 0;
		while (pixel_y < GRID_SIZE)
		{
			mlx_put_pixel(game->scene_buffer, pixel_x + x * GRID_SIZE, pixel_y + y
				* GRID_SIZE, 0x505050FF);
			pixel_y += 1;
		}
		pixel_x += 1;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->width)
	{
		y = 0;
		while (y < game->height)
		{
			if (game->s_map[y][x] == '1')
				fill_square(game, x, y);
			y += 1;
		}
		x += 1;
	}
}

int get_direction_color(t_point *direction)
{
	if (direction->x > 0.0)
		return (0xffbe0bff);
	if (direction->y > 0.0)
		return (0xfb5607ff);
	if (direction->x < 0.0)
		return (0x8338ecff);
	return (0x3a86ffff);
}

void draw_minimap(t_game *game)
{
	t_point	collision;
	t_ray	ray;
	t_point	direction;

	draw_map(game);
	draw_grid(game);
	draw_point(game, &game->start, 0x00FF00FF);
	draw_point(game, &game->end, 0xFF0000FF);
	init_ray(&ray, &game->start, &game->end);
	collide_ray(game, &ray, &collision, &direction);
	draw_point(game, &collision, get_direction_color(&direction));
}