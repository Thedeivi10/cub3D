/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 02:44:41 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/22 04:01:01 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	south(t_game *game, t_point *collisions)
{
	t_point	collision;
	t_point	direction;
	t_point	distance;
	t_ray	ray;
	t_view	view;

	view = game->player;
	view.direction.x = 0.0;
	view.direction.y = 1.0;
	init_ray(&ray, &view);
	collide_ray(game, &ray, &collision, &direction);
	distance.x = collision.x - view.position.x;
	distance.y = collision.y - view.position.y;
	draw_point(game, &collision, 0xffffffff);
	if (v_length(&distance) < COLLISION_DISTANCE)
	{
		draw_point(game, &collision, 0xff0000ff);
		collisions->y = 1.0;
	}
}

static void	north(t_game *game, t_point *collisions)
{
	t_point	collision;
	t_point	direction;
	t_point	distance;
	t_ray	ray;
	t_view	view;

	view = game->player;
	view.direction.x = 0.0;
	view.direction.y = -1.0;
	init_ray(&ray, &view);
	collide_ray(game, &ray, &collision, &direction);
	distance.x = collision.x - view.position.x;
	distance.y = collision.y - view.position.y;
	draw_point(game, &collision, 0xffffffff);
	if (v_length(&distance) < COLLISION_DISTANCE)
	{
		draw_point(game, &collision, 0xff0000ff);
		collisions->y = -1.0;
	}
}

static void	east(t_game *game, t_point *collisions)
{
	t_point	collision;
	t_point	direction;
	t_point	distance;
	t_ray	ray;
	t_view	view;

	view = game->player;
	view.direction.x = 1.0;
	view.direction.y = 0.001;
	init_ray(&ray, &view);
	collide_ray(game, &ray, &collision, &direction);
	distance.x = collision.x - view.position.x;
	distance.y = collision.y - view.position.y;
	draw_point(game, &collision, 0xffffffff);
	if (v_length(&distance) < COLLISION_DISTANCE)
	{
		draw_point(game, &collision, 0xff0000ff);
		collisions->x = 1.0;
	}
}

static void	west(t_game *game, t_point *collisions)
{
	t_point	collision;
	t_point	direction;
	t_point	distance;
	t_ray	ray;
	t_view	view;

	view = game->player;
	view.direction.x = -1.0;
	view.direction.y = 0.001;
	init_ray(&ray, &view);
	collide_ray(game, &ray, &collision, &direction);
	distance.x = collision.x - view.position.x;
	distance.y = collision.y - view.position.y;
	draw_point(game, &collision, 0xffffffff);
	if (v_length(&distance) < COLLISION_DISTANCE)
	{
		draw_point(game, &collision, 0xff0000ff);
		collisions->x = -1.0;
	}
}

void	check_collisions(t_game *game, t_point *collisions)
{
	collisions->x = 0.0;
	collisions->y = 0.0;
	north(game, collisions);
	south(game, collisions);
	east(game, collisions);
	west(game, collisions);
}
