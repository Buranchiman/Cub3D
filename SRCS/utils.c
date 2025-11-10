/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:03:29 by wivallee          #+#    #+#             */
/*   Updated: 2025/11/10 17:43:57 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			i++;
	}
	return (i);
}

//void	delete_texture(t_texture *texture)
//{
//	if (texture->path)
//	{
//		printf("texture path is %s\n", texture->path);
//		free(texture->path);
//	}
//	if (texture->ptr)
//		mlx_destroy_image(get_data()->mlx_ptr, texture->ptr);
//}

//void	del_text_wrapper(void *content)
//{
//	delete_texture((t_texture *)content);
//}

//void	empty_struct_array(void *array, int size, size_t elem_size,
//	void (*del)(void *))
//{
//	int		i;
//	char	*base;
//
//	if (!array || !del)
//		return ;
//	base = (char *)array;
//	i = 0;
//	while (i < size)
//	{
//		del((void *)(base + i * elem_size));
//		i++;
//	}
//}

int	is_all_space_n_ones(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] != '1' && string[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	ft_clean_exit(t_data *data, int option, char *msg)
{
	int i;

	i = 0;
	if (data->map)
		ft_clear_tab(data->map);
	//empty_struct_array(data->texture, 9, sizeof(data->texture[0]), del_text_wrapper);
	if (data->buffer)
		free(data->buffer);
	//to modified
	while (i < 9)
	{
		if (data->texture[i].ptr)	
			mlx_destroy_image(data->mlx_ptr, data->texture[i].ptr);
		//if (data->texture[i].path)	
		//	free(data->texture->path);
		i++;
	}
	if (msg && option == 1)
		ft_printf(2, "\x1b[38;5;196m[Error : %s]\033[0m\n", msg);
	if (msg && option == 0)
		ft_printf(1, "\n%s\n", msg);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (option == 1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int quit_with_int(t_data *data)
{
	ft_clean_exit(data, 1, "See you soon👋\n");
	return (0);
}
