/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:21:35 by davigome          #+#    #+#             */
/*   Updated: 2025/06/02 20:25:47 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_check_num(t_map *game, int i, int aux,int j)
{
	char *temp;

	if (j - aux > 10)
	{
		fprintf(stderr, "Error\nThe texture of f is num,num,num and num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
	temp = ft_substr(game->grid[i], aux, j - 1);
	if (game->grid[i][j - 1] == ',' || game->grid[i][j - 1] <= 32)
	{
		fprintf(stderr, "Error\nThe texture of f is num,num,num and num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
	aux = ft_atoi(temp);
	if (aux > 255 || aux < 0)
	{
		free(temp);
		return -1;
	}
	free(temp);
	return 1;
}

void	ft_check_next(t_map *game, int i,int j)
{
	if (game->grid[i][j - 1] != 10 && game->grid[i][j - 1] != '\0')
	{
		fprintf(stderr, "Error\nThe texture of f and c is num,num,num and num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
}

void	ft_check_text_space(t_map *game, int i, int j)
{
	if (game->grid[i][j + 1] != ' ')
	{
		fprintf(stderr, "Error\nBetween F and C and the colour must be a space.\n");
		ft_bad_close(game);
	}
}

void	ft_check_text_num(t_map *game, int i, int j)
{
	if (game->grid[i][j] > '9' || game->grid[i][j] < '0')
	{
		fprintf(stderr, "Error\nThe texture of f and c is num,num,num and num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
}

void	ft_check_text_comma(t_map *game, int times, int i, int j)
{
	if (times < 2 && game->grid[i][j] != ',')
	{
		fprintf(stderr, "Error\nThe texture of f is num,num,num and num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
}

void	ft_check_f(t_map *game, int i, int j)
{
	int	aux;
	int times;

	aux = -1;
	j = 0;
	times = -1;
	ft_check_text_space(game, i, j);
	while(game->grid[i][++j] <= 32)
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
			fprintf(stderr, "Error\nThe texture of f is num,num,num and num must be between 0 and 255, both include.\n");
			ft_bad_close(game);
		}
	}
	ft_check_next(game, i, j);
}

void	ft_check_c(t_map *game, int i, int j)
{
	int	aux;
	int times;

	aux = -1;
	j = 0;
	times = -1;
	ft_check_text_space(game, i, j);
	while(game->grid[i][++j] <= 32)
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
			fprintf(stderr, "Error\nThe texture of f is num,num,num and num must be between 0 and 255, both include");
			ft_bad_close(game);
		}
	}
	ft_check_next(game, i, j);
}

void	ft_check_elements_3(t_map *game)
{
	int		i;
	int		j;

	i = -1;
	while (game->grid[++i])
	{
		if (game->grid[i][0] != 'N' && game->grid[i][0] != 'S'
			&& game->grid[i][0] != 'W' && game->grid[i][0] != 'E'
			&& game->grid[i][0] != 'F' && game->grid[i][0] != 'C'
			&& game->grid[i][0] != '\n')
			break;
		j = 1;
		if (game->grid[i][0] == 'N')
			ft_check_n(game, i, j);
		if (game->grid[i][0] == 'S')
			ft_check_s(game, i, j);
		if (game->grid[i][0] == 'W')
			ft_check_w(game, i, j);
		if (game->grid[i][0] == 'E')
			ft_check_e(game, i, j);
		if (game->grid[i][0] == 'F')
			ft_check_f(game, i, j);
		if (game->grid[i][0] == 'C')
			ft_check_c(game, i, j);
	}
}

void	ft_check_elements(t_map *game)
{
	t_elem	*elem;
	int		i;

	i = -1;
	elem = malloc(sizeof(t_elem));
	ft_init_elem(elem);
	while (game->grid[++i])
	{
		if (game->grid[i][0] != 'N' && game->grid[i][0] != 'S'
			&& game->grid[i][0] != 'W' && game->grid[i][0] != 'E'
			&& game->grid[i][0] != 'F' && game->grid[i][0] != 'C'
			&& game->grid[i][0] != '\n')
			break;
		ft_check_elements_rep(game, i, elem);
	}
	ft_check_elements_2(game, elem);
	free(elem);
	ft_check_elements_3(game);
}

void	ft_invalid_char(t_map *game, int i)
{
	int j;

	while (game->grid[i])
	{
		j = -1;
		while (game->grid[i][++j])
		{
			if (game->grid[i][j] != '0' && game->grid[i][j] != '1'
				&& game->grid[i][j] != 'N' && game->grid[i][j] != 'S'
				&& game->grid[i][j] != 'E' && game->grid[i][j] != 'W'
				&& game->grid[i][j] > 32)
			{
				fprintf(stderr, "Error\nOnly valid characthers in the map.\n");
				ft_bad_close(game);
			}
		}
		++i;
	}
}

void	ft_init_start(t_start *start)
{
	start->e = 0;
	start->n = 0;
	start->s = 0;
	start->w = 0;
}

void	ft_check_start_2(t_map *game, int i, int j, t_start *start)
{
	if (game->grid[i][j] == 'N')
		++start->n;
	if (game->grid[i][j] == 'S')
		++start->s;
	if (game->grid[i][j] == 'E')
		++start->e;
	if (game->grid[i][j] == 'W')
		++start->w;
}

void	ft_check_start(t_map *game, int i)
{
	t_start	*start;
	int		j;

	start = malloc(sizeof(t_start));
	ft_init_start(start);
	while(game->grid[i])
	{
		j = -1;
		while(game->grid[i][++j])
		{
			ft_check_start_2(game, i, j, start);
		}
		++i;
	}
	if((start->e == 0 && start->n == 0 && start->s == 0 && start->w == 1)
		|| (start->e == 0 && start->n == 0 && start->s == 1 && start->w == 0)
		|| (start->e == 0 && start->n == 1 && start->s == 0 && start->w == 0)
		|| (start->e == 1 && start->n == 0 && start->s == 0 && start->w == 0))
		return ;
	fprintf(stderr, "Error\nOnly one start point.\n");
	free(start);
	ft_bad_close(game);
}

void	ft_flood_fill(char **cpy, int i, int j, t_map *game)
{
	if (cpy[i][j] == '1' || cpy[i][j] == 'V')
		return ;
	if (!cpy[i + 1])
	{
		fprintf(stderr, "Error\nYour map have not the correct structure.\n");
		ft_free_matrix(cpy);
		ft_bad_close(game);
	}
	cpy[i][j] = 'V';
	if ((cpy[i][j + 1] != '0' && cpy[i][j + 1] != 'N' && cpy[i][j + 1] != 'S'
		&& cpy[i][j + 1] != 'E' && cpy[i][j + 1] != 'W' && cpy[i][j + 1] != 'V' && cpy[i][j + 1] != '1') || (cpy[i][j - 1] != '0'
		&& cpy[i][j - 1] != 'N' && cpy[i][j - 1] != 'S'&& cpy[i][j - 1] != 'E' 
		&& cpy[i][j - 1] != 'W' && cpy[i][j - 1] != 'V' && cpy[i][j - 1] != '1') || (cpy[i + 1][j] != '0' && cpy[i + 1][j] != 'N'
		&& cpy[i + 1][j] != 'S'&& cpy[i + 1][j] != 'E' && cpy[i + 1][j] != 'W' && cpy[i + 1][j] != 'V'  && cpy[i + 1][j] != '1')
		|| (cpy[i - 1][j] != '0' && cpy[i - 1][j] != 'N' && cpy[i - 1][j] != 'S'
		&& cpy[i - 1][j] != 'E' && cpy[i - 1][j] != 'W' && cpy[i - 1][j] != 'V' && cpy[i - 1][j] != '1'))
	{
		fprintf(stderr, "Error\nYour map have not the correct structure.\n");
		ft_free_matrix(cpy);
		ft_bad_close(game);
	}
	ft_flood_fill(cpy, i + 1, j, game);
	ft_flood_fill(cpy, i, j + 1, game);
	ft_flood_fill(cpy, i - 1, j, game);
	ft_flood_fill(cpy, i, j - 1, game);
}

void	ft_check_path(t_map *game, int i)
{
	int	j;
	char **cpy;

	j = 0;
	while (game->grid[i])
	{
		j = -1;
		while (game->grid[i][++j])
		{
			if (game->grid[i][j] == '0' || game->grid[i][j] == 'N'
				|| game->grid[i][j] == 'S' || game->grid[i][j] == 'W'
				|| game->grid[i][j] == 'S')
			{
				cpy = ft_cpy_matrix(game->grid);
				ft_flood_fill(cpy, i, j, game);
				ft_free_matrix(cpy);
			}
			
		}
		++i;
	}
}

void	ft_check_map(t_map *game)
{
	int		i;

	i = -1;
	while (game->grid[++i])
	{
		if (game->grid[i][0] != 'N' && game->grid[i][0] != 'S'
			&& game->grid[i][0] != 'W' && game->grid[i][0] != 'E'
			&& game->grid[i][0] != 'F' && game->grid[i][0] != 'C'
			&& game->grid[i][0] != '\n')
			break;
	}
	ft_invalid_char(game, i);
	ft_check_start(game, i);
	ft_check_path(game, i);
}

void	ft_checks(t_map *game, char **argv)
{
	ft_check_name(argv);
	ft_init_map(game);
	ft_read_map(game, argv);
	ft_check_elements(game);
	ft_check_map(game);
}

int main(int argc, char **argv)
{
	t_map *game;
	
	if (argc == 2)
	{
		game = malloc(sizeof(t_map));
		ft_checks(game, argv);
		ft_free_map(game);
	}
	else
	{
		fprintf(stderr, "Error\ncub3D needs a .cub map.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}