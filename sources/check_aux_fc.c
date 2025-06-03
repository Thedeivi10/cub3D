/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_aux_fc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:42:36 by davigome          #+#    #+#             */
/*   Updated: 2025/06/03 18:21:01 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_check_num(t_map *game, int i, int aux, int j)
{
	char	*temp;

	if (j - aux > 10)
	{
		fprintf(stderr, "Error\nThe texture of f is num,num,num and\
			num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
	temp = ft_substr(game->grid[i], aux, j - 1);
	if (game->grid[i][j - 1] == ',' || game->grid[i][j - 1] <= 32)
	{
		fprintf(stderr, "Error\nThe texture of f is num,num,num and\
			num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
	aux = ft_atoi(temp);
	if (aux > 255 || aux < 0)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	return (1);
}

void	ft_check_next(t_map *game, int i, int j)
{
	if (game->grid[i][j - 1] != 10 && game->grid[i][j - 1] != '\0')
	{
		fprintf(stderr, "Error\nThe texture of f and c is num,num,num and");
		fprintf(stderr, "num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
}

void	ft_check_text_space(t_map *game, int i, int j)
{
	if (game->grid[i][j + 1] != ' ')
	{
		fprintf(stderr, "Error\nBetween F and C and the\
			colour must be a space.\n");
		ft_bad_close(game);
	}
}

void	ft_check_text_num(t_map *game, int i, int j)
{
	if (game->grid[i][j] > '9' || game->grid[i][j] < '0')
	{
		fprintf(stderr, "Error\nThe texture of f and c is num,num,num\
			and num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
}

void	ft_check_text_comma(t_map *game, int times, int i, int j)
{
	if (times < 2 && game->grid[i][j] != ',')
	{
		fprintf(stderr, "Error\nThe texture of f is num,num,num\
			and num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
}
