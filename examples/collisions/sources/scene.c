/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:06:09 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/22 04:01:31 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

static int	get_direction_color(t_point *direction)
{
	if (direction->x > 0.0)
		return (0xffbe0bff);
	if (direction->y > 0.0)
		return (0xfb5607ff);
	if (direction->x < 0.0)
		return (0x8338ecff);
	return (0x3a86ffff);
}

static void	draw_column(t_game *game, t_view *view, int column, double angle)
{
	t_point	collision;
	t_point	direction;
	t_ray	ray;
	double	height;
	int		row;

	init_ray(&ray, view);
	collide_ray(game, &ray, &collision, &direction);
	collision.x -= game->player.position.x;
	collision.y -= game->player.position.y;
	height = SCREEN_HEIGHT / sqrt(collision.x * collision.x + collision.y
			* collision.y) / cos(angle);
	row = SCREEN_HEIGHT / 2 - height / 2;
	while (row < SCREEN_HEIGHT / 2 + height / 2)
	{
		if (row > 0 && row < SCREEN_HEIGHT)
			mlx_put_pixel(game->buffer, column, row,
				get_direction_color(&direction));
		row += 1;
	}
}

static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			if (y < SCREEN_HEIGHT / 2)
				mlx_put_pixel(game->buffer, x, y, game->scene.ceiling_color);
			else
				mlx_put_pixel(game->buffer, x, y, game->scene.floor_color);
			y += 1;
		}
		x += 1;
	}
}

void	draw_scene(t_game *game)
{
	int		column;
	t_view	view;
	double	angle;

	column = 0;
	draw_background(game);
	angle = FOV / 2.0;
	view = game->player;
	rotate_view(&view, angle);
	while (column < SCREEN_WIDTH)
	{
		rotate_view(&view, -FOV / SCREEN_WIDTH);
		angle -= FOV / SCREEN_WIDTH;
		draw_column(game, &view, column, angle);
		column += 1;
	}
}
