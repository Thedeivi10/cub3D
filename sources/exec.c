/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:40:25 by jotrujil          #+#    #+#             */
/*   Updated: 2025/06/03 14:08:14 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	execute(t_map *map)
{
	t_mlx	mlx;

	mlx.player = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.tex = (t_textures *)ft_calloc(sizeof(t_textures), 1);
	mlx.mlx_pointer = mlx_init(SIZE_W, SIZE_H, "cub3D", false);
	if (!mlx.mlx_pointer)
		return(mlx_exit(&mlx), 0); //TODO: Create mlx_exit function to destroy all related to the MLX
}