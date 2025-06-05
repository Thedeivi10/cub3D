/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:33:00 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/20 19:30:47 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "caster.h"
#include <math.h>

void	init_ray_scale(t_point *scale, t_point *start, t_point *end)
{
	double	delta_x;
	double	delta_y;
	double	x_over_y;
	double	y_over_x;

	delta_x = end->x - start->x;
	delta_y = end->y - start->y;
	x_over_y = delta_x / delta_y;
	y_over_x = delta_y / delta_x;
	scale->x = sqrt(1 + (y_over_x * y_over_x));
	scale->y = sqrt(1 + (x_over_y * x_over_y));
}

void	next_intersection(t_point *scale, t_point *start, t_point *end)
{
	t_point	inc;
	t_point	dir;
	t_point	horizontal;
	t_point	vertical;

	dir.y = (end->y > start->y) * 2 - 1;
	dir.x = (end->x > start->x) * 2 - 1;
	inc.y = (end->y > start->y) - fmod(start->y, 1.0);
	inc.y -= (!inc.y) * 1.0;
	inc.x = (end->x > start->x) - fmod(start->x, 1.0);
	inc.x -= (!inc.x) * 1.0;
	horizontal.y = start->y + inc.y;
	horizontal.x = start->x + dir.x * dir.y * inc.y * scale->y / scale->x;
	vertical.y = start->y + dir.y * dir.x * inc.x * scale->x / scale->y;
	vertical.x = start->x + inc.x;
	if ((horizontal.x - vertical.x) * dir.x > 0)
	{
		start->x = vertical.x;
		start->y = vertical.y;
		return ;
	}
	start->x = horizontal.x;
	start->y = horizontal.y;
}
