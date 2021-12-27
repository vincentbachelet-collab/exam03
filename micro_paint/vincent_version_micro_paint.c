/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vincent_version_micro_paint.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:45:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/27 18:43:07 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "stdio.h"
#include "math.h"

typedef struct s_root
{
	char	r;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
} t_root;

int		W;
int		H;
char	BG;
char	**tab;

int	err_msg(FILE *file, int err)
{
	int i;
	
	i = 0;
	if (err == 2 && (err = 1))
		write(1, "Error: Operation file corrupted\n", 32);
	else if (err == 1)
		write(1, "Error: argument\n", 16);
	else
	{
		while (i < H)
		{
			write(1, tab[i], W);
			write(1, "\n", 1);
			i++;
		}
	}
	if (file)
		fclose(file);
	return (err);
}

int in_rect(float row, float col, t_root *root)
{
	if (col < root->x || root->x + root->width < col || row < root->y || root->y + root->height < row)
		return (0);
	if ((col - root->x < 1.00000000) || root->x + root->width - col < 1.00000000 || row - root->y < 1.00000000|| root->y + root->height - row < 1.00000000)
		return (1);
	return (2);
}

int main(int argc, char **argv)
{
	FILE	*file;
	int		check_scanf;
	int		i;
	t_root	root;
	int 	row;
	int		col;
	int		rect;

	if (argc != 2)
		return (err_msg(file, 1));
	if ((file = fopen(argv[1], "r")))
	{
		if (check_scanf = fscanf(file, "%d %d %c", &W, &H, &BG) == 3)
		{
			if (W > 0 && W <= 300 && H > 0 && H <= 300)
			{
				tab = malloc(sizeof(char *) * H);
				if (tab == 0)
					return (err_msg(file, 0));
				i = 0;
				while (i < H)
				{
					tab[i] = malloc(sizeof(char) * W);
					if (tab[i] == 0)
						return (err_msg(file, 0));
					memset(tab[i], BG, W); 
					i++;
				}
				while (1)
				{
					check_scanf = fscanf(file, "\n%c %f %f %f %f %c", &root.r, &root.x, &root.y, &root.width, &root.height, &root.color);
					if (check_scanf == -1)
						return (err_msg(file, 0));
					else if (check_scanf != 6 || root.width <= 0 || root.height <= 0 || (root.r != 'R' && root.r != 'r'))
						break;
					row = 0;
					while (row < H)
					{
						col = 0;
						while (col < W)
						{
							rect = in_rect(row, col, &root);
							if ((rect == 1 && root.r == 'r') || ((rect == 2 || rect == 1) && root.r == 'R'))
								tab[row][col] = root.color;
							col++;
						}
						row++;
					}
				}
			}
		}
	}
	return (err_msg(file, 2));
}

