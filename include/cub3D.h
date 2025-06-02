/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:18:30 by davigome          #+#    #+#             */
/*   Updated: 2025/06/02 12:22:55 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <unistd.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_map
{
	char	**grid;
	int		height;
}				t_map;

typedef struct s_elem
{
	int	n;
	int s;
	int e;
	int w;
	int c;
	int f;
}				t_elem;

typedef struct s_start
{
	int	n;
	int	s;
	int	e;
	int	w;
}				t_start;

#endif
