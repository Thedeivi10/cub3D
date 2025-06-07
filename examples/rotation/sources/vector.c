/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:21:12 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/23 02:54:57 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_.h"
#include <math.h>

void	norm(t_point *vector)
{
	double	length;

	if (!vector->x && !vector->y)
		return ;
	length = v_length(vector);
	vector->x /= length;
	vector->y /= length;
}

double	v_length(t_point *vector)
{
	return (sqrt(vector->x * vector->x + vector->y * vector->y));
}
