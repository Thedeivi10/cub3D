/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:33:00 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/22 04:01:27 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void	init_ray(t_ray *ray, t_view *view)
{
	ray->direction = view->direction;
	ray->scale.x = (ray->direction.y / ray->direction.x);
	ray->scale.y = (ray->direction.x / ray->direction.y);
	ray->start = view->position;
	ray->direction = view->direction;
}

static t_point	*get_intersection(t_point *horizontal, t_point *vertical,
		t_point *displacement, t_point *dir)
{
	if (horizontal->x == vertical->x)
	{
		displacement->x += dir->x;
		displacement->y += dir->y;
		dir->y = 0.0;
		return (vertical);
	}
	else if ((horizontal->x - vertical->x) * dir->x >= 0)
	{
		displacement->x += dir->x;
		dir->y = 0.0;
		return (vertical);
	}
	else
	{
		displacement->y += dir->y;
		dir->x = 0.0;
		return (horizontal);
	}
}

static void	intersect_ray(t_ray *ray, t_point *intersection,
		t_point *displacement, t_point *dir)
{
	t_point	increment;
	t_point	horizontal;
	t_point	vertical;

	dir->y = (ray->direction.y > 0) * 2 - 1;
	dir->x = (ray->direction.x > 0) * 2 - 1;
	increment.y = (ray->direction.y > 0) - fmod(intersection->y, 1.0);
	increment.y -= (!increment.y);
	increment.x = (ray->direction.x > 0) - fmod(intersection->x, 1.0);
	increment.x -= (!increment.x);
	horizontal.y = intersection->y + increment.y;
	horizontal.x = intersection->x + increment.y * ray->scale.y;
	vertical.y = intersection->y + increment.x * ray->scale.x;
	vertical.x = intersection->x + increment.x;
	*intersection = *get_intersection(&horizontal, &vertical, displacement,
			dir);
}

static int	check_collision(t_game *game, t_point *position,
		t_point *displacement)
{
	t_point	new_position;

	new_position.x = ((int)position->x) + displacement->x;
	new_position.y = ((int)position->y) + displacement->y;
	if ((int)new_position.y < 0 || (int)new_position.y >= game->height
		|| (int)new_position.y < 0 || (int)new_position.y >= game->width)
		return (0);
	return (game->s_map[(int)new_position.y][(int)new_position.x] == '1');
}

void	collide_ray(t_game *game, t_ray *ray, t_point *collision,
		t_point *direction)
{
	t_point	next;
	t_point	displacement;
	int		intersections;

	displacement.x = 0.0;
	displacement.y = 0.0;
	intersections = game->height + game->width;
	next = ray->start;
	while (intersections && !check_collision(game, &ray->start, &displacement))
	{
		intersect_ray(ray, &next, &displacement, direction);
		*collision = next;
		intersections -= 1;
	}
}
