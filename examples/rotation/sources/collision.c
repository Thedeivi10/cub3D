/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 02:44:41 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/23 03:15:48 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_.h"
#include <math.h>

static void	collision(t_game *game, double x, double y, t_point *collisions)
{
	t_point	collision;
	t_point	direction;
	t_point	distance;
	t_ray	ray;
	t_view	view;

	x += 0.001;
	y += 0.001;
	view = game->player;
	view.direction.x = x;
	view.direction.y = y;
	init_ray(&ray, &view);
	collide_ray(game, &ray, &collision, &direction);
	distance.x = collision.x - view.position.x;
	distance.y = collision.y - view.position.y;
	if (game->debug_mode)
		draw_point(game, &collision, 0xffffffff);
	if (v_length(&distance) < COLLISION_DISTANCE * v_length(&view.direction))
	{
		if (game->debug_mode)
			draw_point(game, &collision, 0xff0000ff);
		collisions->x += round(x);
		collisions->y += round(y);
	}
}

void	check_collisions(t_game *game, t_point *collisions)
{
	collisions->x = 0.0;
	collisions->y = 0.0;
	collision(game, 0.0, 1.0, collisions);
	collision(game, 1.0, 0.0, collisions);
	collision(game, 0.0, -1.0, collisions);
	collision(game, -1.0, 0.0, collisions);
	collision(game, -1.0, -1.0, collisions);
	collision(game, -1.0, 1.0, collisions);
	collision(game, 1.0, -1.0, collisions);
	collision(game, 1.0, 1.0, collisions);
}
