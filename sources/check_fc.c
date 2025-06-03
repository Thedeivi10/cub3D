/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:47:03 by davigome          #+#    #+#             */
/*   Updated: 2025/06/03 18:50:05 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_check_f(t_map *game, int i, int j)
{
	int	aux;
	int	times;

	aux = -1;
	j = 0;
	times = -1;
	ft_check_text_space(game, i, j);
	while (game->grid[i][++j] <= 32)
		;
	while (++times < 3)
	{
		aux = j;
		ft_check_text_num(game, i, j);
		while (game->grid[i][j] >= '0' && game->grid[i][j] <= '9')
			++j;
		ft_check_text_comma(game, times, i, j);
		if (ft_check_num(game, i, aux, j++) == -1)
		{
			fprintf(stderr, "Error\nThe texture of f is num,num,num and ");
			fprinf(stderr, "num must be between 0 and 255, both include.\n");
			ft_bad_close(game);
		}
	}
	ft_check_next(game, i, j);
}

void	ft_check_c(t_map *game, int i, int j)
{
	int	aux;
	int	times;

	aux = -1;
	j = 0;
	times = -1;
	ft_check_text_space(game, i, j);
	while (game->grid[i][++j] <= 32)
		;
	while (++times < 3)
	{
		aux = j;
		ft_check_text_num(game, i, j);
		while (game->grid[i][j] >= '0' && game->grid[i][j] <= '9')
			++j;
		ft_check_text_comma(game, times, i, j);
		if (ft_check_num(game, i, aux, j++) == -1)
		{
			fprintf(stderr, "Error\nThe texture of f is num,num,num and ");
			fprintf(stderr, "num must be between 0 and 255, both include.\n");
			ft_bad_close(game);
		}
	}
	ft_check_next(game, i, j);
}
