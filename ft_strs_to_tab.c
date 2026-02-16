#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_stock_str
{
	int		size;
	char	*str;
	char	*copy;
}	t_stock_str;

void		ft_show_tab(t_stock_str *par);
void		ft_putchar(int num);
t_stock_str	*ft_error(int arr_count, struct s_stock_str *array);
t_stock_str	*ft_strs_to_tab(int ac, char **av);
int			ft_strlen(char *str);
void		ft_strcpy(char *dest, char *src);

t_stock_str	*ft_error(int arr_count, t_stock_str *array)
{
	while (arr_count >= 0)
	{
		free(array[arr_count].str);
		free(array[arr_count].copy);
		arr_count--;
	}
	free(array);
	return (NULL);
}

t_stock_str	*ft_str_allocation(int ac, t_stock_str *array,
char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		array[i].str = malloc(ft_strlen(av[i]) + 1);
		if (array[i].str == NULL)
			return (ft_error(i - 1, array));
		array[i].copy = malloc(ft_strlen(av[i]) + 1);
		if (array[i].copy == NULL)
			return (ft_error(i - 1, array));
		i++;
	}
	return (array);
}

t_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	int			i;
	t_stock_str	*array;

	array = malloc(sizeof(t_stock_str) * (ac + 1));
	if (!array)
		return (NULL);
	if (ft_str_allocation(ac, array, av) == NULL)
		return (NULL);
	i = 0;
	while (i < ac)
	{
		ft_strcpy(array[i].str, av[i]);
		ft_strcpy(array[i].copy, av[i]);
		array[i].size = ft_strlen(av[i]);
		i++;
	}
	array[i].str = 0;
	array[i].copy = 0;
	return (array);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_strcpy(char *dest, char *src)
{
	while (*src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
}

void ft_show_tab(t_stock_str *par)
{
	int j;

	while (par->str != NULL)
	{
		j = 0;
		while (par->str[j] != '\0')
		{
			write(1, &(par->str[j]), 1);
			j++;
		}
		write(1, "\n", 1);
		ft_putchar(par->size);
		write(1, "\n", 1);
		j = 0;
		while (par->copy[j] != '\0')
		{
			write(1, &(par->copy[j]), 1);
			j++;
		}
		write(1, "\n\n", 2);
		par++;
	}
}

void ft_putchar(int num)
{
	char c;
	if (num <= 9)
	{
		c = num + '0';
		write(1, &c, 1);
		return;
	}
	else
	{
		ft_putchar(num / 10);
		c = (num % 10) + '0';
		write(1, &c, 1);
	}
}

int main(void)
{
	int ac = 6;
	char *texts[6] = {"new",   "sample", "text",
					  "APPLE", "BANANA", "Growth begins where comfort ends"};
	t_stock_str *array = ft_strs_to_tab(ac, texts);
	if (!array)
		return (1);
	ft_show_tab(array);
	while (ac >= 1)
	{
		free(array[ac - 1].str);
		free(array[ac - 1].copy);
		ac--;
	}
	free(array);
	return (0);
}
