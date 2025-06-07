/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:06:09 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/21 19:41:19 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "caster.h"
#include <math.h>

void	draw_column(t_game *game, int column, t_point *end, double angle)
{
	t_point	collision;
	t_point	direction;
	t_ray	ray;
	double	height;
	int		row;

	init_ray(&ray, &game->start, end);
	collide_ray(game, &ray, &collision, &direction);
	collision.x -= game->start.x;
	collision.y -= game->start.y;
	height = GRID_SIZE * game->height / sqrt(collision.x * collision.x
			+ collision.y * collision.y) / cos(angle);
	row = game->height * GRID_SIZE / 2 - height / 2;
	while (row < game->height * GRID_SIZE / 2 + height / 2)
	{
		if (row > 0 && row < game->height * GRID_SIZE)
			mlx_put_pixel(game->scene_buffer, column, row,
					get_direction_color(&direction));
		row += 1;
	}
}

void	rotate_position(t_point *start, t_point *end, double angle)
{
	t_point	vector;
	double	cos_;
	double	sin_;

	cos_ = cos(angle);
	sin_ = sin(angle);
	vector.x = end->x - start->x;
	vector.y = end->y - start->y;
	end->x = vector.x * cos_ + vector.y * sin_;
	end->y = vector.x * -sin_ + vector.y * cos_;
	end->x = start->x + end->x;
	end->y = start->y + end->y;
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->render_columns)
	{
		y = 0;
		while (y < game->height * GRID_SIZE)
		{
			if (y < game->height * GRID_SIZE / 2)
				mlx_put_pixel(game->scene_buffer, x + game->width * GRID_SIZE,
						y, game->scene.ceiling_color);
			else
				mlx_put_pixel(game->scene_buffer, x + game->width * GRID_SIZE,
						y, game->scene.floor_color);
			y += 1;
		}
		x += 1;
	}
}

void	draw_scene(t_game *game)
{
	int		column;
	t_point	end;
	double	angle;

	if (game->scene_buffer)
		mlx_delete_image(game->mlx, game->scene_buffer);
	game->scene_buffer = mlx_new_image(game->mlx, game->width * GRID_SIZE
			+ game->render_columns, game->height * GRID_SIZE);
	if (!game->scene_buffer)
		return ;
	column = 0;
	draw_background(game);
	angle = (FOV / 2.0);
	end = game->end;
	rotate_position(&game->start, &end, angle);
	while (column < game->render_columns)
	{
		end = game->end;
		rotate_position(&game->start, &end, angle);
		angle -= FOV / (double)game->render_columns;
		draw_column(game, column + game->width * GRID_SIZE, &end, angle);
		column += 1;
	}
}
