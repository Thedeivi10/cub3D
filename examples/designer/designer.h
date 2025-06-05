/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-b <plopez-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:15:04 by plopez-b          #+#    #+#             */
/*   Updated: 2023/09/30 19:22:01 by plopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESIGNER_H
# define DESIGNER_H

# include <MLX42/MLX42.h>

# define GRID_SIZE 10

typedef struct s_game
{
	char			*name;
	char			*filename;
	char			*title;
	int				fd;
	unsigned int	width;
	unsigned int	height;
	unsigned int	start_column;
	unsigned int	start_row;
	unsigned int	end_column;
	unsigned int	end_row;
	char			*map;
	mlx_t			*mlx;
	mlx_image_t		*buffer;
}					t_game;

#endif