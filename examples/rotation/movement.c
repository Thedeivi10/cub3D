/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:29:57 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/23 02:54:43 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_.h"
#include <math.h>

void	rotate_view(t_view *view, double angle)
{
	double	cos_;
	double	sin_;

	cos_ = cos(angle);
	sin_ = sin(angle);
	view->direction.x = view->direction.x * cos_ + view->direction.y * sin_;
	view->direction.y = view->direction.x * -sin_ + view->direction.y * cos_;
	norm(&view->direction);
}

void	move_view(t_game *game, t_view *view, t_point *direction)
{
	t_point	movement;
	t_point	collisions;

	norm(direction);
	direction->x *= PLAYER_SPEED;
	direction->y *= PLAYER_SPEED;
	check_collisions(game, &collisions);
	movement.x = direction->x * view->direction.x + direction->y
		* view->direction.y;
	movement.y = direction->x * view->direction.y - direction->y
		* view->direction.x;
	if (collisions.x * movement.x <= 0)
		view->position.x += movement.x;
	if (collisions.y * movement.y <= 0)
		view->position.y += movement.y;
}
