/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:33:00 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/21 16:57:15 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "caster.h"
#include <math.h>
#include <stdio.h>

void	init_ray(t_ray *ray, t_point *start, t_point *end)
{
	t_point	delta;

	delta.x = end->x - start->x;
	delta.y = end->y - start->y;
	ray->scale.x = (delta.y / delta.x);
	ray->scale.y = (delta.x / delta.y);
	ray->start = *start;
	ray->end = *end;
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

void	intersect_ray(t_ray *ray, t_point *intersection, t_point *displacement,
		t_point *dir)
{
	t_point	inc;
	t_point	horizontal;
	t_point	vertical;

	dir->y = (ray->end.y > ray->start.y) * 2 - 1;
	dir->x = (ray->end.x > ray->start.x) * 2 - 1;
	inc.y = (ray->end.y > ray->start.y) - fmod(intersection->y, 1.0);
	inc.y -= (!inc.y);
	inc.x = (ray->end.x > ray->start.x) - fmod(intersection->x, 1.0);
	inc.x -= (!inc.x);
	horizontal.y = intersection->y + inc.y;
	horizontal.x = intersection->x + inc.y * ray->scale.y;
	vertical.y = intersection->y + inc.x * ray->scale.x;
	vertical.x = intersection->x + inc.x;
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
	while (intersections && !check_collision(game, &game->start, &displacement))
	{
		intersect_ray(ray, &next, &displacement, direction);
		*collision = next;
		intersections -= 1;
	}
}
