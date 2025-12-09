#include "../INCLUDE/cube.h"

void	take_tex_out(char ***map, int end)
{
	int		i;
	char	**temp;

	i = 0;
	temp = *map;
	while (i < end)
	{
		free(temp[i]);
		i++;
	}
	ft_memmove(*map, &temp[i], (ft_tablen(&temp[i]) + 1) * sizeof(char *));
}

void	free_img(t_img *img)
{
	t_data	*d;

	d = get_data();
	if (img)
	{
		if (img->img)
			mlx_destroy_image(d->mlx, img->img);
		free (img);
	}
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < NBR_TEXTURES)
	{
		if (data->tex[i].ptr)
			free_img(data->tex[i].ptr);
		if (data->tex[i].path)
			free(data->tex[i].path);
		if (data->tex[i].pixels)
			free(data->tex[i].pixels);
		i++;
	}
	if (data->sky_path)
		free(data->sky_path);
	if (data->sky.path)
		free(data->sky.path);
	if (data->sky.ptr)
		free_img(data->sky.ptr);
	if (data->sky.pixels)
		free(data->sky.pixels);
	if (data->tab_m)
		free(data->tab_m);
	if (data->tab_doors)
		free(data->tab_doors);
}

void	ft_clean_exit(t_data *data, int option, char *msg)
{
	mlx_mouse_show(data->mlx, data->win_ptr);
	mlx_do_key_autorepeaton(data->mlx);
	mlx_loop_end(data->mlx);
	free_data(data);
	if (data->map)
		ft_clear_tab(data->map);
	if (data->buffer)
		free(data->buffer);
	if (data->mlx_img)
		free_img(data->mlx_img);
	if (msg && option == 1)
		ft_printf(2, "\x1b[38;5;196m[Error : %s]\033[0m\n", msg);
	if (msg && option == 0)
		ft_printf(1, "\x1b[38;5;55m[%s]\033[0m\n", msg);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx, data->win_ptr);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	system("pkill mpg123");
	system("stty sane");
	if (option == 1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
