/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:06:09 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/22 07:20:01 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

static void	draw_column(t_game *game, t_view *view, int column, double angle)
{
	t_texture_column	col;
	int					row;

	init_ray(&col.ray, view);
	collide_ray(game, &col.ray, &col.collision, &col.direction);
	col.image.x = fmod(col.collision.x, 1.0);
	col.image.x += (!col.image.x) * fmod(col.collision.y, 1.0);
	col.distance.x = col.collision.x - game->player.position.x;
	col.distance.y = col.collision.y - game->player.position.y;
	col.height = SCREEN_HEIGHT / v_length(&col.distance) / cos(angle);
	row = SCREEN_HEIGHT / 2 - col.height / 2;
	while (row < SCREEN_HEIGHT / 2 + col.height / 2)
	{
		col.image.y = (row - (SCREEN_HEIGHT / 2 - col.height / 2)) / col.height;
		if (row > 0 && row < SCREEN_HEIGHT)
			mlx_put_pixel(game->buffer, column, row,
				get_texture_pixel(get_texture_from_direction(game,
						&col.direction), &col.image, &col.direction));
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
