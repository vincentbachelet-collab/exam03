/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vincent_mini_paint.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:45:33 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/27 17:42:34 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

typedef struct s_root
{
	char 	c;
	float	x;
	float	y;
	float	radius;
	char	color;
	
}	t_root;

int		W;
int		H;
char	BG;
char	**tab;

int err_msg(FILE *file, int err)
{
	int	i;
	
	if (err = 2 && (err = 1))
		write(1, "Error: Operation file corrupted\n", 32);
	else if (err == 1)
		write(1, "Error: argument\n", 16);
	else 
	{
		i = 0;
		while (i < H)
		{
			write (1, tab[i], W);
			write(1, "\n", 1);
		}
	}
	if (file)
		close(file);
	return (err);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	int		check_fscanf;
	int		i;
	t_root	root;
	int 	row;
	int 	col;
	float 	sqr;

	file = NULL;
	if (argc != 2)
		return (err_msg(file, 1));
	if ((file = fopen(argv[1], "r")))
	{
		if ((check_fscanf = fscanf(file, "%d %d %c", &W, &H, &BG)) == 3)
		{
			if (W > 0 && W <= 300 && H > 0 && H <= 300)
			{
				tab = malloc(sizeof(char *) * H);
				if (tab == 0)
					return (err_msg(file, 0));
				i = 0;
				while (i < H)
				{
					tab[i] = malloc(sizeof(char *) * W); 
					if (tab[i] == 0)
						return (err_msg(file, 0));
					memset(tab[i], BG, W);
					i++;
				}
			}
			while (1)
			{
				check_fscanf = fscanf(file,"\n%c %f %f %f %c", &root.c, &root.x, &root.y, &root.radius, &root.color);
				if (check_fscanf == -1)
					return (err_msg(file, 0));
				else if (check_fscanf != 5 || root.radius <= 0 || (root.c != 'c' && root.c != 'C'))
					break;
				row = 0;
				while (row < H)
				{
					col = 0;
					while (col < W)
					{
						sqr = sqrtf((powf(row - root.x, 2)) + (powf(col - root.y, 2)));
						if (sqr <= root.radius)
						{
							if ((sqr + 1 > root.radius && root.c == 'c') || root.c == 'C')
								tab[row][col] = root.color;
						}
						col++;
					}
					row++;
				}
			}
		
		}
	}
	return (err_msg(file, 2));
}