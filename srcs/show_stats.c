/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_stats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:32:37 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/30 14:12:50 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int		print_header_stat(char *name, int *tab, int size, int step)
{
	int		quant;

	ft_printf("%~{255;255;0}Printing  %~{255;0;0}%s\t\t%~{155;155;255}%s\n",
	name, name);
	ft_printf("%~{255;255;0}Possesses %~{155;155;255}%d%~{255;255;0} values\t",
	size);
	ft_printf("Ranging from %~{155;155;255}%d%~{255;255;0}", tab[0]);
	ft_printf(" to %~{155;155;255}%d\n", tab[size - 1]);
	ft_printf("%~{255;255;0}Whith step of %~{155;155;255}%d%~{255;255;0}  \t",
	step);
	quant = (size / 1000) + 1;
	quant = 1;
	ft_printf("Compression factor: %~{155;155;255}%d%~{255;255;0}\n", quant);
	return (quant);
}

int		print_step(int *x, int quant, int seuil, int len)
{
	int i;

	if (*x / quant)
		ft_printf("%0*d", *x / quant, 0);
	i = 0;
	while ((*x - i++) % quant > 0)
		ft_printf(".");
	*x = 0;
	if (len)
		ft_printf("\n%~{255;150;150}%*d%~{}|%~{150;255;150}", len, seuil);
	return (1);
}

void	print_tab(char *name, int *tab, int step, int size)
{
	int		seuil;
	int		len;
	int		i;
	int		x;
	int		quant;

	i = 0;
	len = ft_nb_len(tab[size - 1], 0) + 2;
	seuil = tab[i];
	x = 0;
	quant = print_header_stat(name, tab, size, step);
	ft_printf("\n%~{255;150;150}%*d%~{}|%~{150;255;150}", len, seuil);
	while (i < size)
	{
		if (tab[i] < seuil + step)
			x++;
		else
			i -= print_step(&x, quant, seuil += step, len);
		i++;
	}
	seuil += step;
	print_step(&x, quant, seuil += step, 0);
	ft_printf("\n");
}

int		get_tab_from_file(char *str, int **tab)
{
	size_t		fd;
	int			i;
	char		*line;

	fd = open(str, O_RDONLY);
	*tab = ft_memalloc(sizeof(int) * 5000);
	i = -1;
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		(*tab)[i] = ft_atoi(ft_strchr(line, ':') + 2);
		(*tab)[i] = ft_atoi(line);
	}
	close(fd);
	return (i + 1);
}

int		main(int ac, char **av)
{
	int		*tab;
	int		size;
	int		range;

	if (ac == 1)
		return (0);
	(void)av;
	size = get_tab_from_file("./data/data.lem-in", &tab);
	ft_squick_sort(&tab, 0, size - 1);
	range = tab[size - 1] - tab[0];
	range /= 50;
	if (!range)
		range++;
	print_tab("./data/data.lem-in", tab, range, size);
	return (0);
}
